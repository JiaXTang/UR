#pragma once
#ifdef DLL_EXPORT
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif // DLL_EXPORT

#include <string>
using namespace std;

#define		SYNCING			2
#define		STARTED 		1
#define		STOPPED			0

struct DLL_API sixDoubleStruct
{
	double v_1;
	double v_2;
	double v_3;
	double v_4;
	double v_5;
	double v_6;
};

class DLL_API IURInterface
{
public:
	// 建立RTClient与机械臂的连接
	/*
     * 功能：连接到机械臂，与其建立通信
     * 注意：RTClient与机械臂建立了通信，DashBoard的连接操作不需要程序员管理
     * 返回：true->连接成功  false->连接失败
     */
	virtual bool ConnectToUR() = 0;

	// 断开RTClient与机械臂的连接
	virtual void CloseConnectToUR() = 0;
		
	// 上电
	/*
     * 功能：通过DashBoard客户端给UR上电
     * 返回：C++ native的string，表示上电结果
     */
	virtual string PowerOn() = 0;
		
	// 下电
	/*
     * 功能：通过DashBoard客户端给UR下电
     * 返回：C++ native的string，表示下电结果
     */
	virtual string PowerOff() = 0;
		
	// 解除刹车
	/*
     * 功能：通过DashBoard客户端给UR解除刹车
     * 返回：C++ native的string，表示刹车结果
     */
	virtual string BreakRelease() = 0;
		
	// 断电
	/*
     * 功能：通过DashBoard客户端给UR断电
     * 返回：C++ native的string，表示断电结果
     */
	virtual string Shutdown() = 0;
		
	// 回到零点
	/*
     * 功能：回到UR的零点位置
     * 返回：true->命令已发送 false->命令未发送
     */
	virtual bool GoBackZero() = 0;
		
	// 设置起始位置
	/*
     * 默认的起始位置:
     * {机座(90°),肩部(-90°), 肘部(90°), 手腕(-90°), 手腕2(-90°), 手腕3(0°)}
     */
	virtual void SetStartPos(sixDoubleStruct in_startPos) = 0;
	 	
	// 回到起始位置
	virtual bool GoBackStart() = 0;

	// 基座负方向移动
	virtual void DecBaseJoint() = 0;
	// 基座正方向移动
	virtual void AddBaseJoint() = 0;
	// 肩部负方向移动
	virtual void DecShoulderJoint() = 0;
	// 肩部正方向移动
	virtual void AddShoulderJoint() = 0;
	// 肘部负方向移动
	virtual void DecElbowJoint() = 0;
	// 肘部正方向移动
	virtual void AddElbowJoint() = 0;
	// 手腕1负方向移动
	virtual void DecWrist1Joint() = 0;
	// 手腕1正方向移动
	virtual void AddWrist1Joint() = 0;
	// 手腕2负方向移动
	virtual void DecWrist2Joint() = 0;
	// 手腕2正方向移动
	virtual void AddWrist2Joint() = 0;
	// 手腕3负方向移动
	virtual void DecWrist3Joint() = 0;
	// 手腕3正方向移动
	virtual void AddWrist3Joint() = 0;

	// tcp位置调整 Z轴负方向移动
	virtual void TcpPosZDec() = 0;
	// tcp位置调整 Z轴正方向移动
	virtual void TcpPosZAdd() = 0;
	// tcp位置调整 Y轴负方向移动
	virtual void TcpPosYDec() = 0;
	// tcp位置调整 Y轴正方向移动
	virtual void TcpPosYAdd() = 0;
	// tcp位置调整 X轴负方向移动
	virtual void TcpPosXDec() = 0;
	// tcp位置调整 X轴正方向移动
	virtual void TcpPosXAdd() = 0;

	// tcp方向调整 tcpZ轴方向在角度变小的趋势移动
	virtual void TcpDirZDec() = 0;
	// tcp方向调整 tcpZ轴方向在角度变大的趋势移动
	virtual void TcpDirZAdd() = 0;
	// tcp方向调整 tcpY轴方向在角度变小的趋势移动
	virtual void TcpDirYDec() = 0;
	// tcp方向调整 tcpY轴方向在角度变大的趋势移动
	virtual void TcpDirYAdd() = 0;
	// tcp方向调整 tcpX轴方向在角度变小的趋势移动
	virtual void TcpDirXDec() = 0;
	// tcp方向调整 tcpX轴方向在角度变大的趋势移动
	virtual void TcpDirXAdd() = 0;


	// 获取当前tcp的位置数据
	/*
     * 功能：获取tcp当前的位置数据
     * 注意：结构tcpActPos中各个double元素的单位是:
     *		{v_1(mm), v_2(mm), v_3(mm), v_4(rad), v_5(rad), v_6(rad)}
     * 参数：输入sixDoubleStruct变量的引用，获得的位置信息存储在该引用之中
     * 注意：由于C#SDK的错误，v_3的输出值比实际值要大400mm，因此在显示该值时，需要手动减去400mm的差值
     */
	virtual void GetTcpActualPos(sixDoubleStruct& tcpActPos) = 0;

	// 获取UR六轴的角度数据
	/*
     * 功能：获取UR六轴的位置数据
     * 注意：结构tcpJoiPos中各个double元素的单位是角度，也即°，如57.22°
     * 参数：输入sixDoubleStruct变量的引用，获得的各个关节的角度信息存储在该引用之中
     */
	virtual void GetTcpJointsPos(sixDoubleStruct& tcpJoiPos) = 0;
		
	// 移动到指定位置
	/*
     * 功能：给定一个TCP位置参数，控制UR机械臂移动到此处
     * 注意：其中参数是位置信息inTargetPos:
     *		{x(mm), y(mm), z(mm), Rx(Rad), Ry(Rad), Rz(Rad)}
     */
	virtual void GoToTargetPos(sixDoubleStruct inTargetPos) = 0;
	// 停止所以关节的运动
	virtual void StopAllJoint() = 0;
	// 获取连接状态
	/*
     * 返回结果有三种状态:
     * SYNCING(同步)			2
     * STARTED(启动) 		1
     * STOPPED(停止)			0
     */
	virtual unsigned char GetConnectionStatus() = 0;

	// 虚析构函数
	virtual ~IURInterface() {}
};

DLL_API IURInterface* CreateURer(char* ip);



