#include <chrono>
#include <cstddef>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_two_ints.hpp"

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  if (argc != 3) {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Uso: add_two_ints_client X Y");
    return 1;
  }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_two_ints_client");
  rclcpp::Client<tutorial_interfaces::srv::AddTwoInts>::SharedPtr client =
    node->create_client<tutorial_interfaces::srv::AddTwoInts>("add_two_ints");

  auto request = std::make_shared<tutorial_interfaces::srv::AddTwoInts::Request>();
  request->a = atoll(argv[1]);
  request->b = atoll(argv[2]);

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrotto mentre attendevo il servizio.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Servizio non disponibile, riprovo...");
  }

  auto result = client->async_send_request(request);

  // Attesa della risposta
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Risultato del calcolo dal server: %ld", result.get()->sum);
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Fallita la chiamata al servizio");
  }

  rclcpp::shutdown();
  return 0;
}
