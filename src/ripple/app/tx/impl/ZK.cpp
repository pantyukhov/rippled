//------------------------------------------------------------------------------
/*
    This file is part of rippled: https://github.com/ripple/rippled
    Copyright (c) 2023 Ripple Labs Inc.

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#include <ripple/app/tx/impl/ZK.h>

#include <ripple/basics/Log.h>
#include <ripple/ledger/ApplyView.h>
#include <ripple/ledger/View.h>
#include <ripple/protocol/Feature.h>
#include <ripple/protocol/Indexes.h>
#include <ripple/protocol/TxFlags.h>
#include <ripple/protocol/st.h>

namespace ripple {

/*
    ZK
    ======

    Decentralized Identifiers (ZKs) are a new type of identifier that enable
    verifiable, self-sovereign digital identity and are designed to be
    compatible with any distributed ledger or network. This implementation
    conforms to the requirements specified in the ZK v1.0 specification
    currently recommended by the W3C Credentials Community Group
    (https://www.w3.org/TR/zk-core/).
*/

//------------------------------------------------------------------------------
extern "C" {
    int proof_verify(const char* gadget_ptr, const char* proof_str, char* err_message, size_t err_length);
}



NotTEC
ZKSet::preflight(PreflightContext const& ctx)
{
    return preflight2(ctx);
}

TER
ZKSet::doApply()
{
    std::vector<uint8_t> params_bytes = {0x01, 0x02, 0x03, 0x04};
    std::vector<uint8_t> proof = {0x01, 0x05, 0x06, 0x07};
    uint32_t hamming_dist = 10;  // Example Hamming distance

    const char* path = "/home/pavel/Projects/zk_verify/rust/local";
    const char* gadget_path =  "/home/pavel/Projects/zk_verify/rust/local";
    const char* proof_path =  "/home/pavel/Projects/zk_verify/rust/src/tests/example.zkif";

    // Call the Rust function
    char error_message[256]; // Buffer for potential error message

    // Call the Rust function
    int result = proof_verify(gadget_path, proof_path, error_message, sizeof(error_message));

    if (result) {
        return tesSUCCESS;
    }
    return tecNOTVALID_ZK;
}

}  // namespace ripple
