#include <cstddef>
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_two_ints.hpp"

#include <memory>

void handle_sum(const std::shared_ptr<tutorial_interfaces::srv::AddTwoInts::Request> request,
                  std::shared_ptr<tutorial_interfaces::srv::AddTwoInts::Response> response)
{
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ricevuta richiesta: a = %ld, b = %ld", request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Invio risposta di calcolo (somma): %ld", response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_server");

  rclcpp::Service<tutorial_interfaces::srv::AddTwoInts>::SharedPtr service =
    node->create_service<tutorial_interfaces::srv::AddTwoInts>("add_two_ints", &handle_sum);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Server di calcolo pronto.");

  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
