#include <iostream>
#include <vector>
#include <tuple>
#include <optional>

#include <zmq.hpp>

class ProcessList {
private:
public:
    using data_t = std::tuple<int, bool>;

    // Храним узлы в списке
    std::vector<data_t> nodes;

    // ID управляющего узла
    int root_id;


    ProcessList(int root_id) : root_id(root_id) {
        // Изначально добавляем только управляющий узел
        nodes.emplace_back(root_id, true);
    }

    void insert(data_t data) {
        // Добавляем новый узел в список
        nodes.push_back(data);
    }

    bool is_in_list(int id) {
        // Проверяем, есть ли узел в списке
        for (const auto& node : nodes) {
            if (std::get<0>(node) == id) return true;
        }
        return false;
    }

    std::optional<data_t> get_by_id(int id) {
        // Получаем данные узла по ID
        for (const auto& node : nodes) {
            if (std::get<0>(node) == id) return node;
        }
        return std::nullopt;
    }

    std::vector<int> get_all_nodes() {
        // Возвращаем список ID всех узлов
        std::vector<int> all_nodes;
        for (const auto& node : nodes) {
            all_nodes.push_back(std::get<0>(node));
        }
        return all_nodes;
    }

    void print_nodes() {
        // Выводим все узлы
        for (const auto& node : nodes) {
            std::cout << "ID: " << std::get<0>(node)
                      << ", Active: " << (std::get<1>(node) ? "Yes" : "No")
                      << '\n';
        }
    }

    ~ProcessList() {
        // Освобождение ресурсов (если потребуется)
        zmq::context_t ctx;
        for (const auto& node : nodes) {
            int id = std::get<0>(node);
            zmq::socket_t socket(ctx, ZMQ_REQ);
            socket.connect("ipc:///tmp/lab5_" + std::to_string(id));
            // socket.send(zmq::buffer(std::string("die\n")), zmq::send_flags::none);
        }
    }
};
