- 环境：Linux
- 步骤：
<br>1、将main.cpp、规则集文件、数据集文件放在同一目录下
<br>2、在此目录中右键选择“在这里打开终端”
<br>3、在输入`gcc main_Linux.cpp -o main`编译
<br>4、输入`chmod +x main`将main设置为可被执行
<br>5、输入`./main <规则集文件名> <数据集文件名>`运行程序，如`./main rule1.txt packet.txt`
- 结果：将在同一目录中生成res.txt
<br><br>
- 环境：Windows
- 步骤：
<br>1、将main.cpp、规则集文件、数据集文件放在同一目录下
<br>2、在此目录中右键选择“在 Windows终端 中打开”（没有的话可以在Microsoft Store搜索Windows Terminal获取，当然用Git Bash也是可以的，总之要能执行shell命令，别用cmd）
<br>3、在输入`gcc main_Windows.cpp -o main`编译
<br>4、输入`./main <规则集文件名> <数据集文件名>`运行程序，如`./main rule1.txt packet.txt`
- 结果：将在同一目录中生成res.txt
