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
#include "WordHyphenator.hpp"

#include <Constants/Chars.hpp>

using namespace Minibook;

WordHyphenator::WordHyphenator( Stream<std::wstring>& source )
    : m_source( source )
    , m_rules{ { L"gssssg", 3 },
               { L"gsssg", 3 },
               { L"gsssg", 2 },
               { L"sggg", 2 },
               { L"gssg", 2 },
               { L"sggs", 2 },
               { L"sgsg", 2 },
               { L"xgg", 1 },
               { L"xsg", 1 },
               { L"xgs", 1 },
               { L"xss", 1 } }
{
    // TODO: Use Unicode literals
    m_classes['x'] = L"\x0439\x044C\x044A"                                           // йьъ
                     L"\x041A\x042C\x042A";                                          // ЙЬЪ
    m_classes['g'] = L"\x0430\x0435\x0451\x0438\x043E\x0443\x044B\x044D\x044E\x044F" // аеёиоуыэюя
                     L"\x0410\x0415\x0401\x0418\x041E\x0423\x042B\x042D\x042E\x042F" // АЕЁИОУЫЭЮЯ
                     L"AEIOUYaeiouy";
    m_classes['s'] = L"\x0431\x0432\x0433\x0434\x0436\x0437\x043a\x043b\x043c\x043d" // бвгджзклмн
                     L"\x043f\x0440\x0441\x0442\x0444\x0445\x0446\x0447\x0448\x0449" // прстфхцчшщ
                     L"\x0411\x0412\x0413\x0414\x0416\x0417\x041A\x041B\x041C\x041D" // БВГДЖЗКЛМН
                     L"\x041F\x0420\x0421\x0422\x0424\x0425\x0426\x0427\x0428\x0429" // ПРСТФХЦЧШЩ
                     L"BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz";
}

std::wstring WordHyphenator::Fetch()
{
    if ( m_chunks.empty() )
    {
        std::wstring word = m_source.Fetch();
        if ( word.empty() )
            return {};

        m_chunks = Hyphenate( std::move( word ) );
    }

    std::wstring syllable = m_chunks.front();
    m_chunks.pop_front();
    return syllable;
}

WordHyphenator::ChunkList WordHyphenator::Split( std::wstring_view text, wchar_t separator )
{
    ChunkList parts;

    for ( size_t index = 0; ( index = text.find( separator ) ) != std::wstring::npos; )
    {
        parts.push_back( std::wstring( text.substr( 0, index ) ) + Chars::kSoftHyphen );

        text = text.substr( index + 1 );
    }

    parts.emplace_back( text );
    return parts;
}

WordHyphenator::ChunkList WordHyphenator::Hyphenate( std::wstring word )
{
    std::wstring pattern;

    // prepare word pattern
    for ( const wchar_t letter : word )
    {
        // TODO: Use direct mapping char to class instead searching
        auto found = std::find_if( m_classes.begin(),
                                   m_classes.end(),
                                   [letter]( auto& item ) -> bool
                                   {
                                       return item.second.find( letter ) != std::wstring::npos;
                                   } );

        if ( found == m_classes.end() )
            pattern += letter;
        else
            pattern += found->first;
    }

    // match word pattern and add soft hypenations
    for ( const auto& rule : m_rules )
    {
        for ( size_t index = pattern.find( rule.first ); index != std::wstring::npos;
              index = pattern.find( rule.first ) )
        {
            const size_t actualIndex = index + rule.second;

            pattern = pattern.substr( 0, actualIndex ) + Chars::kSoftHyphen
                      + pattern.substr( actualIndex );

            word = word.substr( 0, actualIndex ) + Chars::kSoftHyphen + word.substr( actualIndex );
        }
    }

    return Split( word, Chars::kSoftHyphen );
}
