/*
 * Copyright (C) 2016-2022 Konstantin Polevik
 * All rights reserved
 *
 * This file is part of the Minibook. Redistribution and use in source and
 * binary forms, with or without modification, are permitted exclusively
 * under the terms of the MIT license. You should have received a copy of the
 * license with this file. If not, please visit:
 * https://github.com/out61h/minibook/blob/main/LICENSE
 */
#include "UnicodeDecoder.hpp"

#include <Exceptions/BadUnicodeData.hpp>
#include <Exceptions/UnknownEncoding.hpp>

#include <cstdio>

using namespace Minibook;

UnicodeDecoder::UnicodeDecoder( OctetStream& source )
    : m_source( source )
    , m_state( State::ExpectedBOM )
{
}

std::optional<wchar_t> UnicodeDecoder::Fetch()
{
    if ( m_state == State::ExpectedBOM )
    {
        auto state = State::ExpectedBOM;

        for ( ; state < State::Terminated; )
        {
            const auto byte = m_source.Fetch();
            if ( !byte )
                return {};

            // TODO: Use table FSM
            switch ( *byte )
            {
            case 0xef:
                if ( state == State::ExpectedBOM )
                    state = State::ExpectedBB;
                else
                    state = State::Failed;

                break;

            case 0xbb:
                if ( state == State::ExpectedBB )
                    state = State::ExpectedBF;
                else
                    state = State::Failed;

                break;

            case 0xbf:
                if ( state == State::ExpectedBF )
                    state = State::DetectedUTF8;
                else
                    state = State::Failed;

                break;

            default:
                state = State::Failed;
                break;
            }
        }

        if ( state == State::Failed )
            throw Exceptions::UnknownEncoding();

        m_state = state;
    }

    auto state = State::ReadFirstOctet;
    wchar_t result = 0;

    for ( ; state < State::Terminated; )
    {
        const auto byte = m_source.Fetch();
        if ( !byte )
            return {};

        const unsigned data = *byte;

        // TODO: Use table FSM
        if ( state == State::ReadFirstOctet )
        {
            if ( ( data & 0x80 ) == 0 )
            {
                result = data & 0x7f;
                state = State::Succeeded;
            }
            else if ( ( data & 0xe0 ) == 0xc0 )
            {
                result = data & 0x1f;
                state = State::ReadOneOctet;
            }
            else if ( ( data & 0xf0 ) == 0xe0 )
            {
                result = data & 0x0f;
                state = State::ReadTwoOctets;
            }
            else if ( ( data & 0xf8 ) == 0xf0 )
            {
                result = data & 0x07;
                state = State::ReadThreeOctets;
            }
            else
            {
                state = State::Failed;
            }
        }
        else if ( state == State::ReadOneOctet )
        {
            result <<= 6;
            result |= data & 0x3f;

            state = State::Succeeded;
        }
        else if ( state == State::ReadTwoOctets )
        {
            result <<= 6;
            result |= data & 0x3f;

            state = State::ReadOneOctet;
        }
        else if ( state == State::ReadThreeOctets )
        {
            result <<= 6;
            result |= data & 0x3f;

            state = State::ReadTwoOctets;
        }
    }

    if ( state == State::Failed )
        throw Exceptions::BadUnicodeData();

    return result;
}
