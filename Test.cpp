#include "doctest.h"
#include "OrgChart.hpp"
#include <vector>

using namespace std;
using namespace ariel;

TEST_CASE("Orgchart constructor"){
    CHECK_NOTHROW(OrgChart organization);
}

TEST_CASE("ADD ROOT"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("CEO"));
    CHECK_NOTHROW(organization.add_root("CTO"));
    CHECK_NOTHROW(organization.add_root("CAO"));
    CHECK_NOTHROW(organization.add_root("CBO"));
    CHECK_NOTHROW(organization.add_root("CCO"));
    CHECK_NOTHROW(organization.add_root("CDO"));
    CHECK_NOTHROW(organization.add_root("CFO"));
}

TEST_CASE("ADD SUB"){
    OrgChart organization;
    organization.add_root("CEO");
    CHECK_THROWS(organization.add_sub("CTO", "CAO"));
    CHECK_NOTHROW(organization.add_sub("CEO", "CTO"));
    CHECK_NOTHROW(organization.add_sub("CEO", "CBO"));
    CHECK_NOTHROW(organization.add_sub("CEO", "CCO"));
    CHECK_NOTHROW(organization.add_sub("CTO", "CDO"));
    CHECK_NOTHROW(organization.add_sub("CDO", "CFO"));
    CHECK_NOTHROW(organization.add_sub("CFO", "CGO"));
}

TEST_CASE("LEVEL_ORDER_ITERATOR"){
    OrgChart organization;
    organization.add_root("1");
    organization.add_sub("1", "1.1");
    organization.add_sub("1", "1.2");
    organization.add_sub("1", "1.3");
    organization.add_sub("1.1", "1.1.1");
    organization.add_sub("1.1", "1.1.2");
    organization.add_sub("1.1", "1.1.3");
    organization.add_sub("1.1", "1.1.4");
    organization.add_sub("1.2", "1.2.1");
    organization.add_sub("1.2", "1.2.2");
    organization.add_sub("1.3", "1.3.1");
    organization.add_sub("1.3", "1.3.2");
    vector<string> ans = {"1", "1.1", "1.2", "1.3", "1.1.1", "1.1.2", "1.1.3", "1.1.4", "1.2.1", "1.2.2", "1.3.1", "1.3.2"};
    size_t count = 0;
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        CHECK(ans[count].compare((*it)));
        count++;
    }
}

TEST_CASE("PREORDER_ITERATOR"){
    OrgChart organization;
    organization.add_root("1");
    organization.add_sub("1", "1.1");
    organization.add_sub("1", "1.2");
    organization.add_sub("1", "1.3");
    organization.add_sub("1.1", "1.1.1");
    organization.add_sub("1.1", "1.1.2");
    organization.add_sub("1.1", "1.1.3");
    organization.add_sub("1.1", "1.1.4");
    organization.add_sub("1.2", "1.2.1");
    organization.add_sub("1.2", "1.2.2");
    organization.add_sub("1.3", "1.3.1");
    organization.add_sub("1.3", "1.3.2");
    vector<string> ans = {"1", "1.1", "1.1.1", "1.1.2", "1.1.3", "1.1.4", "1.2", "1.2.1", "1.2.2", "1.3", "1.3.1", "1.3.2"};
    size_t count = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it){
        CHECK(ans[count].compare((*it)));
        count++;
    }
}

TEST_CASE("REVERSE_ORDER_ITERATOR"){
    OrgChart organization;
    organization.add_root("1");
    organization.add_sub("1", "1.1");
    organization.add_sub("1", "1.2");
    organization.add_sub("1", "1.3");
    organization.add_sub("1.1", "1.1.1");
    organization.add_sub("1.1", "1.1.2");
    organization.add_sub("1.1", "1.1.3");
    organization.add_sub("1.1", "1.1.4");
    organization.add_sub("1.2", "1.2.1");
    organization.add_sub("1.2", "1.2.2");
    organization.add_sub("1.3", "1.3.1");
    organization.add_sub("1.3", "1.3.2");
    vector<string> ans = {"1.1.1", "1.1.2", "1.1.3", "1.1.4", "1.2.1", "1.2.2", "1.3.1", "1.3.2", "1.1", "1.2", "1.3", "1"};
    size_t count = 0;
    for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it){
        CHECK(ans[count].compare((*it)));
        count++;
    }
    
}

TEST_CASE("NORMAL ITERATOR"){
    OrgChart organization;
    organization.add_root("1");
    organization.add_sub("1", "1.1");
    organization.add_sub("1", "1.2");
    organization.add_sub("1", "1.3");
    organization.add_sub("1.1", "1.1.1");
    organization.add_sub("1.1", "1.1.2");
    organization.add_sub("1.1", "1.1.3");
    organization.add_sub("1.1", "1.1.4");
    organization.add_sub("1.2", "1.2.1");
    organization.add_sub("1.2", "1.2.2");
    organization.add_sub("1.3", "1.3.1");
    organization.add_sub("1.3", "1.3.2");
    vector<string> ans = {"1", "1.1", "1.2", "1.3", "1.1.1", "1.1.2", "1.1.3", "1.1.4", "1.2.1", "1.2.2", "1.3.1", "1.3.2"};
    size_t count = 0;
    for (auto element : organization){
        CHECK(ans[count].compare(element));
        count++;
    }
}

TEST_CASE("SIZE"){
    OrgChart organization;
    organization.add_root("1");
    organization.add_sub("1", "1.1");
    organization.add_sub("1", "1.2");
    organization.add_sub("1", "1.3");
    organization.add_sub("1.1", "1.1.1");
    organization.add_sub("1.1", "1.1.2");
    organization.add_sub("1.1", "1.1.3");
    organization.add_sub("1.1", "1.1.4");
    organization.add_sub("1.2", "1.2.1");
    organization.add_sub("1.2", "1.2.2");
    organization.add_sub("1.3", "1.3.1");
    organization.add_sub("1.3", "1.3.2");
    size_t count = 0;
    vector<int> ans = {1, 3, 3, 3, 5, 5, 5, 5, 5, 5, 5, 5};
    for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        CHECK(it->size()== ans[count]);
    }
}
