#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>
#include <map>
#include "../s_list.hpp"

static ProcessList processes(0);

std::map<int, std::string> node_map;

void create_node(int child_id) {
    if (processes.is_in_list(child_id)) {
        return;
    }
    processes.insert(std::make_tuple(child_id, true));
    node_map[child_id] = "";
}

void exec_command(int child_id, const std::string& var, const std::string& value) {
    if (!processes.is_in_list(child_id)) {
        return;
    }
    node_map[child_id] = value;
}

void pingall(std::vector<int>& nodes_with_values) {
    nodes_with_values.clear();
    for (const auto& [node_id, value] : node_map) {
        if (!value.empty()) {
            nodes_with_values.push_back(node_id);
        }
    }
}

TEST(ProcessTest, CreateNodeTest) {
    create_node(1);
    EXPECT_TRUE(processes.is_in_list(1));

    create_node(2);
    EXPECT_TRUE(processes.is_in_list(2));
}

TEST(ProcessTest, PingAllTest) {
    create_node(1);
    exec_command(1, "MyVar", "10");
    create_node(2);
    exec_command(2, "MyVar", "20");
    create_node(3);

    std::vector<int> nodes_with_values;
    pingall(nodes_with_values);

    EXPECT_EQ(nodes_with_values.size(), 2);
    EXPECT_EQ(nodes_with_values[0], 1);
    EXPECT_EQ(nodes_with_values[1], 2);
}

TEST(ProcessTest, MultipleNodesTest) {
    create_node(1);
    create_node(2);
    create_node(3);
    exec_command(1, "Var1", "100");
    exec_command(2, "Var2", "200");

    std::vector<int> nodes_with_values;
    pingall(nodes_with_values);

    EXPECT_EQ(nodes_with_values.size(), 2);
    EXPECT_EQ(nodes_with_values[0], 1);
    EXPECT_EQ(nodes_with_values[1], 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
