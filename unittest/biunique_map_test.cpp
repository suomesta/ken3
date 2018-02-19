/**
 * @file    unittest/biunique_map_test.cpp
 * @brief   Testing ken3::biunique_map using lest. 
 * @author  toda
 * @date    2016-11-24
 * @version 0.1.0
 * @remark  the target is C++11 or more
 */

#include <iterator>
#include <tuple>
#include <vector>
#include "ken3/biunique_map.hpp"
#include "unittest/lest.hpp"

namespace {

// type definitions
template <ken3::biunique_map_type TYPE, ken3::biunique_map_policy POLICY>
using tmp_map = ken3::biunique_map<char, int, TYPE, POLICY>;

using map_list = std::tuple<
    tmp_map<ken3::biunique_map_type::ordered_no_default,    ken3::biunique_map_policy::silence>,
    tmp_map<ken3::biunique_map_type::ordered_front_default, ken3::biunique_map_policy::silence>,
    tmp_map<ken3::biunique_map_type::ordered_back_default,  ken3::biunique_map_policy::silence>,
    tmp_map<ken3::biunique_map_type::unordered_no_default,  ken3::biunique_map_policy::silence>,
    tmp_map<ken3::biunique_map_type::ordered_no_default,    ken3::biunique_map_policy::throwing>,
    tmp_map<ken3::biunique_map_type::ordered_front_default, ken3::biunique_map_policy::throwing>,
    tmp_map<ken3::biunique_map_type::ordered_back_default,  ken3::biunique_map_policy::throwing>,
    tmp_map<ken3::biunique_map_type::unordered_no_default,  ken3::biunique_map_policy::throwing>
>;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief      check std::map items are same or not.
 * @tparam     MAP: std::map.
 * @param[in]  lhs: left hand side.
 * @param[in]  rhs: right hand side.
 * @return     true: same, false: not same.
 */
template <typename MAP>
bool same_map(const MAP& lhs, const typename MAP::map_type& rhs)
{
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (auto i = lhs.cbegin(); i != lhs.cend(); ++i) {
        auto j = rhs.find(i->first);
        if (j == rhs.end()) {
            return false;
        }
        else if (i->second != j->second) {
            return false;
        }
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace {

const lest::test specification[] =
{

    CASE("minimum functions")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
        }
    },

    CASE("iterator constructor with non-duplex data")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            typename my_map::map_type m{{'A', 10}, {'B', 11}};
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("iterator constructor with duplex data")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            my_map bm1(v.begin(), v.end());
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            my_map bm2(m.begin(), m.end());
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT_THROWS_AS((my_map(v.begin(), v.end())), std::invalid_argument);
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            EXPECT_THROWS_AS((my_map(m.begin(), m.end())), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT_THROWS_AS((my_map(v.begin(), v.end())), std::invalid_argument);
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            EXPECT_THROWS_AS((my_map(m.begin(), m.end())), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT_THROWS_AS((my_map(v.begin(), v.end())), std::invalid_argument);
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            EXPECT_THROWS_AS((my_map(m.begin(), m.end())), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            std::vector<typename my_map::value_type> v{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT_THROWS_AS((my_map(v.begin(), v.end())), std::invalid_argument);
            std::map<typename my_map::key_type, typename my_map::mapped_type> m{{'A', 10}, {'B', 11}, {'C', 10}}; // need ordered map to get stable result
            EXPECT_THROWS_AS((my_map(m.begin(), m.end())), std::invalid_argument);
        }
    },

    CASE("initializer_list constructor with non-duplex data")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("initializer_list constructor with duplex data")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2{{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2{{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2{{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2{{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            EXPECT_THROWS_AS((my_map{{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
    },

    CASE("initializer_list assignment with non-duplex data")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            bm = {{'A', 10}, {'B', 11}};
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("initializer_list assignment with duplex data")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1;
            bm1 = {{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2;
            bm2 = {{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1;
            bm1 = {{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2;
            bm2 = {{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1;
            bm1 = {{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2;
            bm2 = {{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1;
            bm1 = {{'A', 10}, {'B', 11}, {'A', 12}};
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            my_map bm2;
            bm2 = {{'A', 10}, {'B', 11}, {'C', 10}};
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm1;
            EXPECT_THROWS_AS((bm1 = {{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            my_map bm2;
            EXPECT_THROWS_AS((bm2 = {{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm1;
            EXPECT_THROWS_AS((bm1 = {{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            my_map bm2;
            EXPECT_THROWS_AS((bm2 = {{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm1;
            EXPECT_THROWS_AS((bm1 = {{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            my_map bm2;
            EXPECT_THROWS_AS((bm2 = {{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm1;
            EXPECT_THROWS_AS((bm1 = {{'A', 10}, {'B', 11}, {'A', 12}}), std::invalid_argument);
            my_map bm2;
            EXPECT_THROWS_AS((bm2 = {{'A', 10}, {'B', 11}, {'C', 10}}), std::invalid_argument);
        }
    },

    CASE("operator==")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(bm1 == bm2);
            EXPECT(bm1 == bm3);
            EXPECT(not (bm1 == bm4));
            EXPECT(not (bm1 == bm5));
        }
    },

    CASE("operator!=")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'A', 10}, {'B', 11}};
            my_map bm3{bm1};
            my_map bm4{{'A', 11}, {'B', 10}};
            my_map bm5;
            EXPECT(not (bm1 != bm2));
            EXPECT(not (bm1 != bm3));
            EXPECT(bm1 != bm4);
            EXPECT(bm1 != bm5);
        }
    },

    CASE("swap()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm1, bm2;
            bm1.insert('A', 10);
            bm1.insert('B', 11);
            bm2.insert('C', 12);
            bm1.swap(bm2);
            EXPECT(same_map(bm1, {{'C', 12}}));
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("size()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            EXPECT(0UL == bm.size());
            bm.insert('A', 10);
            EXPECT(1UL == bm.size());
            bm.insert('B', 11);
            EXPECT(2UL == bm.size());
            bm.clear();
            EXPECT(0UL == bm.size());
        }
    },

    CASE("empty()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            EXPECT(bm.empty());
            bm.insert('A', 10);
            EXPECT(not bm.empty());
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
    },

    CASE("cbegin()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            my_map::map_type m{{'A', 10}, {'B', 11}};
            EXPECT(m.cbegin()->first == bm.cbegin()->first);
            EXPECT(m.cbegin()->second == bm.cbegin()->second);
            EXPECT(std::next(m.cbegin(), 1)->first == std::next(bm.cbegin(), 1)->first);
            EXPECT(std::next(m.cbegin(), 1)->second == std::next(bm.cbegin(), 1)->second);
        }
    },

    CASE("cend()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(std::next(bm.cbegin(), 2) == bm.cend());
        }
    },

    CASE("clear()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm;
            bm.insert('A', 10);
            bm.insert('B', 11);
            EXPECT(not bm.empty());
            bm.clear();
            EXPECT(bm.empty());
        }
    },

    CASE("insert() with non-duplex biunique_map")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}};
            bm2.insert(bm1);
            EXPECT(same_map(bm2, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
    },

    CASE("insert() with duplex biunique_map")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'D', 13}, {'A', 14}};
            my_map bm4{{'E', 14}, {'F', 11}};
            bm1.insert(bm2);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm1.insert(bm3);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm1.insert(bm4);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'D', 13}, {'A', 14}};
            my_map bm4{{'E', 14}, {'F', 11}};
            bm1.insert(bm2);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm1.insert(bm3);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm1.insert(bm4);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'D', 13}, {'A', 14}};
            my_map bm4{{'E', 14}, {'F', 11}};
            bm1.insert(bm2);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm1.insert(bm3);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm1.insert(bm4);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'D', 13}, {'A', 14}};
            my_map bm4{{'E', 14}, {'F', 11}};
            bm1.insert(bm2);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm1.insert(bm3);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm1.insert(bm4);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'C', 12}, {'A', 13}};
            my_map bm4{{'C', 12}, {'D', 10}};
            EXPECT_THROWS_AS(bm1.insert(bm2), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm3), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm4), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'C', 12}, {'A', 13}};
            my_map bm4{{'C', 12}, {'D', 10}};
            EXPECT_THROWS_AS(bm1.insert(bm2), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm3), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm4), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'C', 12}, {'A', 13}};
            my_map bm4{{'C', 12}, {'D', 10}};
            EXPECT_THROWS_AS(bm1.insert(bm2), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm3), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm4), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm1{{'A', 10}, {'B', 11}};
            my_map bm2{{'C', 12}, {'A', 10}};
            my_map bm3{{'C', 12}, {'A', 13}};
            my_map bm4{{'C', 12}, {'D', 10}};
            EXPECT_THROWS_AS(bm1.insert(bm2), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm3), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm1.insert(bm4), std::invalid_argument);
            EXPECT(same_map(bm1, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("insert() with non-duplex initializer_list")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
    },

    CASE("insert() with duplex initializer_list")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}, {'A', 10}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm.insert({{'D', 13}, {'A', 14}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm.insert({{'E', 14}, {'F', 11}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}, {'A', 10}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm.insert({{'D', 13}, {'A', 14}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm.insert({{'E', 14}, {'F', 11}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}, {'A', 10}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm.insert({{'D', 13}, {'A', 14}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm.insert({{'E', 14}, {'F', 11}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert({{'C', 12}, {'A', 10}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
            bm.insert({{'D', 13}, {'A', 14}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            bm.insert({{'E', 14}, {'F', 11}});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert({{'A', 10}, {'C', 12}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'D', 13}, {'A', 14}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'E', 14}, {'F', 11}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert({{'A', 10}, {'C', 12}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'D', 13}, {'A', 14}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'E', 14}, {'F', 11}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert({{'A', 10}, {'C', 12}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'D', 13}, {'A', 14}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'E', 14}, {'F', 11}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert({{'A', 10}, {'C', 12}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'D', 13}, {'A', 14}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert({{'E', 14}, {'F', 11}}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("insert() with non-duplex iterator")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 12}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 15}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}}));
        }
    },

    CASE("insert() with duplex iterator")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            bm.insert(v.cbegin(), v.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            bm.insert(m.cbegin(), m.cend());
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'D', 13}, {'E', 14}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            EXPECT_THROWS_AS(bm.insert(v.cbegin(), v.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            EXPECT_THROWS_AS(bm.insert(m.cbegin(), m.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            EXPECT_THROWS_AS(bm.insert(v.cbegin(), v.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            EXPECT_THROWS_AS(bm.insert(m.cbegin(), m.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            EXPECT_THROWS_AS(bm.insert(v.cbegin(), v.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            EXPECT_THROWS_AS(bm.insert(m.cbegin(), m.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            const std::vector<my_map::value_type> v{{'C', 10}, {'D', 13}};
            EXPECT_THROWS_AS(bm.insert(v.cbegin(), v.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            const my_map::map_type m{{'E', 14}, {'F', 10}};
            EXPECT_THROWS_AS(bm.insert(m.cbegin(), m.cend()), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("insert() with non-duplex pair")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'C', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
    },

    CASE("insert() with duplex pair")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'A', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert(my_map::value_type{'C', 11});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'A', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert(my_map::value_type{'C', 11});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'A', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert(my_map::value_type{'C', 11});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert(my_map::value_type{'A', 12});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert(my_map::value_type{'C', 11});
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'A', 12}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'C', 11}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'A', 12}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'C', 11}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'A', 12}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'C', 11}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'A', 12}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert(my_map::value_type{'C', 11}), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("insert() with non-duplex f and s")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('C', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}, {'C', 12}}));
        }
    },

    CASE("insert() with duplex f and s")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('A', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert('C', 11);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('A', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert('C', 11);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('A', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert('C', 11);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            bm.insert('A', 12);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            bm.insert('C', 11);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert('A', 12), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert('C', 11), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert('A', 12), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert('C', 11), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert('A', 12), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert('C', 11), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT_THROWS_AS(bm.insert('A', 12), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
            EXPECT_THROWS_AS(bm.insert('C', 11), std::invalid_argument);
            EXPECT(same_map(bm, {{'A', 10}, {'B', 11}}));
        }
    },

    CASE("has_f()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            EXPECT(bm.has_f('B'));
            EXPECT(not bm.has_f('C'));
        }
    },

    CASE("has_s()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            EXPECT(bm.has_s(11));
            EXPECT(not bm.has_s(12));
        }
    },

    CASE("erase_by_f()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_f('A'));
            bm.erase_by_f('A');
            EXPECT(not bm.has_f('A'));
            EXPECT(1UL == bm.size());
            bm.erase_by_f('C');
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_f('B'));
            bm.erase_by_f('B');
            EXPECT(not bm.has_f('B'));
        }
    },

    CASE("erase_by_s()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(bm.has_s(10));
            bm.erase_by_s(10);
            EXPECT(not bm.has_s(10));
            EXPECT(1UL == bm.size());
            bm.erase_by_s(12);
            EXPECT(1UL == bm.size());
            EXPECT(bm.has_s(11));
            bm.erase_by_s(11);
            EXPECT(not bm.has_s(11));
        }
    },

    CASE("f2s()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT_THROWS_AS(bm.f2s('C'), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT(10 == bm.f2s('C'));
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT(11 == bm.f2s('C'));
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT_THROWS_AS(bm.f2s('C'), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT_THROWS_AS(bm.f2s('C'), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT(10 == bm.f2s('C'));
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT(11 == bm.f2s('C'));
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT(10 == bm.f2s('A'));
            EXPECT(11 == bm.f2s('B'));
            EXPECT_THROWS_AS(bm.f2s('C'), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.f2s('A'), std::out_of_range);
        }
    },

    CASE("s2f()")
    {
        {
            using my_map = std::tuple_element<0, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT_THROWS_AS(bm.s2f(12), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<1, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT('A' == bm.s2f(12));
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<2, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT('B' == bm.s2f(12));
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<3, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT_THROWS_AS(bm.s2f(12), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<4, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT_THROWS_AS(bm.s2f(12), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<5, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT('A' == bm.s2f(12));
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<6, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT('B' == bm.s2f(12));
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
        {
            using my_map = std::tuple_element<7, map_list>::type;

            my_map bm{{'A', 10}, {'B', 11}};
            EXPECT('A' == bm.s2f(10));
            EXPECT('B' == bm.s2f(11));
            EXPECT_THROWS_AS(bm.s2f(12), std::out_of_range);
            bm.clear();
            EXPECT_THROWS_AS(bm.s2f(10), std::out_of_range);
        }
    },

};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

