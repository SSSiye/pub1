#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <chrono>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1_2");

    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<geometry_msgs::msg::Vector3>("topic_pub1", qos_profile);

    geometry_msgs::msg::Vector3 message;

    rclcpp::WallRate loop_rate(1.0); // 반복주파수를 저장하는 객체(단위Hz)
    while (rclcpp::ok())
    {
        std::cout << "실수값 3개 입력(x,y,z):";
        std::cin >> message.x >>message.y >> message.z;
      
        RCLCPP_INFO(node->get_logger(), "입력한 값: x=%.2f, y=%.2f, z=%.2f", message.x,message.y,message.z);
        mypub->publish(message);
        loop_rate.sleep(); // 반복주파수에서 남은 시간만큼 sleep
    }

  

    rclcpp::shutdown();
    return 0;
}
