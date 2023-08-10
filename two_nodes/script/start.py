
import subprocess

command = ('bash -c "cd ~/ros2_ws \
           && . install/setup.bash \
           && ros2 launch two_nodes two_nodes_launch.py"')

script = subprocess.Popen(command, shell=True)
script.wait()
