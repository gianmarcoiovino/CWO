from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # Definiamo un argomento da riga di comando per il parametro del timer
    timer_arg = DeclareLaunchArgument(
        'timer_period',
        default_value='1000',
        description='Periodo del timer in millisecondi per il publisher'
    )

    # Nodo Publisher con passaggio del parametro
    talker_node = Node(
        package='cpp_pubsub',
        executable='talker',
        name='minimal_publisher',
        parameters=[{
            'timer_period_ms': LaunchConfiguration('timer_period')
        }]
    )

    # Nodo Subscriber
    listener_node = Node(
        package='cpp_pubsub',
        executable='listener',
        name='minimal_subscriber'
    )

    # Restituiamo la descrizione completa del lancio
    return LaunchDescription([
        timer_arg,
        talker_node,
        listener_node
    ])
