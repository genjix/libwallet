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

#ifndef LIBWALLET_URI_HPP
#define LIBWALLET_URI_HPP

#include <boost/optional.hpp>
#include <bitcoin/address.hpp>

namespace libwallet {

typedef boost::optional<libbitcoin::payment_address> optional_address;

struct parameter_pair
{
    std::string key, value;
};

struct uri_parse_result
{
    typedef std::vector<parameter_pair> parameter_list;

    optional_address address;
    parameter_list parameters;
};

bool uri_parse(const std::string& uri, uri_parse_result& result);

/**
 * A decoded bitcoin URI corresponding to BIP 21 and BIP 72.
 * All string members are UTF-8.
 */
struct uri_decode_result
{
    typedef boost::optional<uint64_t> optional_amount;
    typedef boost::optional<std::string> optional_string;

    optional_address address;
    optional_amount amount;
    optional_string label;
    optional_string message;
    optional_string r;
};

bool uri_decode(const std::string& uri, uri_decode_result& result);

/**
 * Parses a bitcoin amount string.
 * @return string value, in satoshis, or -1 for failure.
 */
uint64_t parse_amount(const std::string& amount);

} // libwallet

#endif

