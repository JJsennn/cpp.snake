# cpp.snake
一个用c++语言编写的windows 控制台贪吃蛇，个人人门练习项目。

## 功能

- 20*20的游玩区域
- 蛇自动移动，wsad实时控制
- 食物随机生成
- 吃下食物记录分数
- 撞墙，撞自己检测
- 使用了控制台光标归位减少画面闪烁

## 编译

```bash
g++ greed_snake.cpp -o greed_snake.exe -std=c++17
```

## 运行

```bash
.\greed_snake.exe
```

## 操作

- w；向上
- s；向下
- a；向左
- d；向右
- Ctrl+C；退出游戏

## 主要实现
 
- 使用deque管理蛇身
- 使用Windows 控制台非阻塞输入实现实时控制
- 使用光标归位覆盖原画面，减少画面闪烁
