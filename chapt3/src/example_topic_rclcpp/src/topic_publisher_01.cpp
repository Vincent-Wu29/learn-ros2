#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicPublisher01 : public rclcpp::Node{
    public:
        TopicPublisher01(std::string name) : Node(name){
            RCLCPP_INFO(this->get_logger(), "大家好，我是%s", name.c_str());

            //创建发布者
            command_publisher_ = this->create_publisher<std_msgs::msg::String>("command", 10);
            // 创建定时器
            timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&TopicPublisher01::CallBack, this));
        }

    private:
        // 定义回调函数
        void CallBack(){
            // 创建消息
            std_msgs::msg::String message;
            message.data = "forward";
            // 记录日志
            RCLCPP_INFO(this->get_logger(), "Publisher Publish: %s", message.data.c_str());
            // 发布消息
            command_publisher_->publish(message);
        }

        //声明定时器指针
        rclcpp::TimerBase::SharedPtr timer_;
        //声明话题发布者
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
};

int main(int argc, char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}