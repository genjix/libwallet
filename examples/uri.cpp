/*
 * Copyright (c) 2011-2013 libwallet developers (see AUTHORS)
 *
 * This file is part of libwallet.
 *
 * libwallet is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
/*
  Demonstration of URI utilities.
*/
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

void reset(libwallet::uri_decode_result& result)
{
    result.address.reset();
    result.amount.reset();
    result.label.reset();
    result.message.reset();
    result.r.reset();
}

int main()
{
    // Not needed since we have the uri_decode() tests below.
    /*test_uri_parse("bitcoin:113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD?label=test");
    test_uri_parse("bitcoin:");
    test_uri_parse("bitcorn:");
    test_uri_parse("BITCOIN:?");
    test_uri_parse("Bitcoin:?&");
    test_uri_parse("bitcOin:&");
    test_uri_parse("bitcoin:?x=y");
    test_uri_parse("bitcoin:?x=");
    test_uri_parse("bitcoin:?=y");
    test_uri_parse("bitcoin:?=");
    test_uri_parse("bitcoin:?x");
    test_uri_parse("bitcoin:19z88");
    test_uri_parse("bitcoin:19l88");
    test_uri_parse("bitcoin:19z88?x=http://www.example.com?purchase%3Dshoes");
    test_uri_parse("bitcoin:19z88?name=%E3%83%95"); // UTF-8
    test_uri_parse("bitcoin:19z88?name=%3");
    test_uri_parse("bitcoin:19z88?name=%3G");
    test_uri_parse("bitcoin:19z88?name=%3f");
    test_uri_parse("bitcoin:%31");
    test_uri_parse("bitcoin:113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD?label=Some joker");
    */

    libwallet::uri_decode_result result;
    bool success = false;
    success = libwallet::uri_decode(
        "bitcoin:113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(result.address &&
        result.address.get().encoded() == "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD");
    BITCOIN_ASSERT(!result.amount);
    BITCOIN_ASSERT(!result.label);
    BITCOIN_ASSERT(!result.message);
    BITCOIN_ASSERT(!result.r);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:19z88", result);
    BITCOIN_ASSERT(!success);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?=", result);
    BITCOIN_ASSERT(!success);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?amount=4.2", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(!result.address);
    BITCOIN_ASSERT(result.amount && result.amount.get() == 420000000);
    BITCOIN_ASSERT(!result.label);
    BITCOIN_ASSERT(!result.message);
    BITCOIN_ASSERT(!result.r);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?amount=.", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(!result.address);
    BITCOIN_ASSERT(result.amount && result.amount.get() == 0);
    BITCOIN_ASSERT(!result.label);
    BITCOIN_ASSERT(!result.message);
    BITCOIN_ASSERT(!result.r);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?amount=4.2.4", result);
    BITCOIN_ASSERT(!success);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?amount=foo", result);
    BITCOIN_ASSERT(!success);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?label=Bob", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(!result.address);
    BITCOIN_ASSERT(!result.amount);
    BITCOIN_ASSERT(result.label && result.label.get() == "Bob");
    BITCOIN_ASSERT(!result.message);
    BITCOIN_ASSERT(!result.r);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?message=Hi%20Alice", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(!result.address);
    BITCOIN_ASSERT(!result.amount);
    BITCOIN_ASSERT(!result.label);
    BITCOIN_ASSERT(result.message && result.message.get() == "Hi Alice");
    BITCOIN_ASSERT(!result.r);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?r=http://www.example.com?purchase%3Dshoes", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(!result.address);
    BITCOIN_ASSERT(!result.amount);
    BITCOIN_ASSERT(!result.label);
    BITCOIN_ASSERT(!result.message);
    BITCOIN_ASSERT(result.r &&
        result.r.get() == "http://www.example.com?purchase=shoes");

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:?foo=ignore", result);
    BITCOIN_ASSERT(success);
    success = libwallet::uri_decode(
        "bitcoin:?req-foo=die", result);
    BITCOIN_ASSERT(!success);

    reset(result);
    success = libwallet::uri_decode(
        "bitcoin:113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD?label=Some joker", result);
    BITCOIN_ASSERT(success);
    BITCOIN_ASSERT(result.address &&
        result.address.get().encoded() == "113Pfw4sFqN1T5kXUnKbqZHMJHN9oyjtgD");
    BITCOIN_ASSERT(!result.amount);
    BITCOIN_ASSERT(result.label && result.label.get() == "Some joker");
    BITCOIN_ASSERT(!result.message);
    BITCOIN_ASSERT(!result.r);

    return 0;
}

