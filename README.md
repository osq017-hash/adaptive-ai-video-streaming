# Adaptive AI Video Streaming

## 项目简介

本项目面向 Linux 应用层开发，构建一个 AI 感知的低延迟视频自适应传输系统。

系统计划实现视频采集、编码、网络传输、接收显示、端到端延迟统计、画面复杂度分析以及 DeepSeek 辅助决策等功能。

## 技术路线

- C++17
- Linux
- CMake
- Socket 网络编程
- 多线程
- OpenCV / FFmpeg
- RTP / UDP
- DeepSeek API

## 计划模块

- video capture：视频采集模块
- encoder：视频编码模块
- network：网络传输模块
- receiver：接收显示模块
- monitor：延迟、丢包、FPS 统计模块
- ai analyzer：画面复杂度分析模块
- policy engine：自适应策略模块
- llm advisor：DeepSeek 辅助决策模块

## 当前进度

- [x] 建立项目仓库
- [x] 搭建 CMake 工程
- [x] 创建 sender / receiver 基础程序
- [ ] 实现 TCP 通信
- [ ] 实现 UDP 通信
- [ ] 实现摄像头采集
- [ ] 实现视频传输
