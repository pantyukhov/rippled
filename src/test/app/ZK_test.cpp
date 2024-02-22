#include <ripple/basics/strHex.h>
#include <ripple/protocol/Feature.h>
#include <ripple/protocol/Indexes.h>
#include <ripple/protocol/TxFlags.h>
#include <ripple/protocol/jss.h>
#include <test/jtx.h>

#include <algorithm>
#include <iterator>

namespace ripple {
namespace test {



struct ZK_test : public beast::unit_test::suite
{
    // Helper function that returns the owner count of an account root.
    std::uint32_t
    ownerCount(test::jtx::Env const& env, test::jtx::Account const& acct)
    {
        std::uint32_t ret{0};
        if (auto const sleAcct = env.le(acct))
            ret = sleAcct->at(sfOwnerCount);
        return ret;
    }


    void
    testZkVerify(FeatureBitset features)
    {
        testcase("featureZK Enabled");

        using namespace jtx;
        // If the ZK amendment is not enabled, you should not be able
        // to set or delete ZKs.
        Env env{*this, features - featureZK};
        Account const alice{"alice"};
        env.fund(XRP(5000), alice);
        env.close();


        BEAST_EXPECT(ownerCount(env, alice) == 0);
        env(zk::setValid(alice), ter(temDISABLED));
        env.close();


//        BEAST_EXPECT(ownerCount(env, alice) == 0);
//        env(zk::setValid(alice), ter(temDISABLED));
//        env.close();

//        BEAST_EXPECT(ownerCount(env, alice) == 0);
//        env(zk::del(alice), ter(temDISABLED));
//        env.close();
    }


    void
    run() override
    {
        using namespace test::jtx;
        FeatureBitset const all{
            supported_amendments() | FeatureBitset{featureZK}};
        testZkVerify(all);
    }
};
BEAST_DEFINE_TESTSUITE_PRIO(ZK, app, ripple, 10000);
//BEAST_DEFINE_TESTSUITE(ZK, app, ripple);
}  // namespace test
}  // namespace ripple
