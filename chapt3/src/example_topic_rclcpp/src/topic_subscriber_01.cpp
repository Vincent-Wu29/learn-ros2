#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscriber01 : public rclcpp::Node{
    public:
        TopicSubscriber01(std::string name) : Node(name) {
            RCLCPP_INFO(this->get_logger(), "大家好，我是%s", name.c_str());
             // 创建一个订阅者订阅话题
            command_subscriber_ = this->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&TopicSubscriber01::command_callback, this, std::placeholders::_1));
        } 

    private:
        // 声明一个订阅者
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber_;
        // 回调函数
        void command_callback(std_msgs::msg::String message){
            float speed = 0.0f;
            if (message.data == "forward"){
                speed = 0.2f;
            }
            RCLCPP_INFO(this->get_logger(), "收到[%s]指令, 速度更改为：%f", message.data.c_str(), speed);
        }
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<TopicSubscriber01>("topic_subscriber_01");

    rclcpp::spin(node);

    rclcpp::shutdown();

    return 0;
}