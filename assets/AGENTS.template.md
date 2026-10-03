# AGENTS.md — {{PROJECT_NAME}}

> 本文件是 AI Agent 接手本工程的第一入口。最后更新：{{DATE}}

## 项目简介

{{一句话说明产品是什么、做什么}}

- 目标芯片 / 模组：{{CHIP_MODULE}}
- SDK：{{SDK_NAME_AND_VERSION}}
- 开发板：{{BOARD_VENDOR_MODEL}}（硬件档案：`docs/hardware/board.md`）

## 关键目录

```
{{REPO_ROOT}}
├── main/                  # 入口与调度（app_main 只做初始化与组装）
│   └── board/             # 板级适配
│       └── board_pins.h   # 引脚事实唯一来源（红线文件）
├── components/            # 纯逻辑组件（不允许直接操作硬件）
├── docs/hardware/         # 硬件档案、安全契约、bring-up 清单
├── host_test/             # 宿主测试（不需要开发板）
└── PRD.md / PROGRESS.md   # 需求入口 / 进度接力棒（最新置顶）
```

## 构建与测试

```powershell
# 宿主测试（纯逻辑，秒级反馈）
cmake -S host_test -B build-host -DCMAKE_BUILD_TYPE=Debug
cmake --build build-host
ctest --test-dir build-host --output-on-failure

# 固件构建（Windows 低并发，避免 cc1 拉起失败 / 1455 页面文件错误）
$env:IDF_PY_BUILD_JOBS='2'
idf.py build
```

烧录与监视（**必须由人工确认目标设备后执行**）：

```powershell
idf.py -p {{COM_PORT}} flash monitor
```

## 分层纪律

1. 纯逻辑（协议、状态机、消抖、映射、路由）放 `components/`，禁止出现 GPIO/I2C 等硬件调用，必须有宿主测试。
2. 硬件操作只在 `main/board` 与平台层，薄层只调用已测试的纯逻辑，不复制第二套算法。
3. 所有引脚只能引用 `board_pins.h` 中的宏，业务代码禁止写裸引脚号。
4. 多板型用编译宏分支区分（如 `#if defined({{BOARD_MACRO}})`），不做全局搜索替换。

## 红线（未经显式授权不得修改）

- `main/board/board_pins.h` 的引脚分配（改错可能短路、烧件）
- 分区表与 NVS 布局（改错可能变砖、丢数据）
- BOOT / strapping 引脚相关启动逻辑（GPIO0/3/45/46）
- {{PERIPHERAL_POWER_RAIL_DESCRIPTION}}（共用电源轨时序）
- 对外通信契约与设备身份：{{PROTOCOL_AND_IDENTITY}}
- 真实凭据不得入库；烧录/擦除 flash 必须人工确认

## 硬件相关工作前置阅读

涉及引脚、BOOT、USB、音频、电源、睡眠唤醒时，动手前必读：

- `docs/hardware/board.md`
- `docs/hardware/bring-up-checklist.md`

## 证据分级（汇报时必须分开，不得互相冒充）

构建成功 ≠ 宿主测试通过 ≠ 烧录成功 ≠ 实板功能正常。
每次任务收尾分别汇报四项状态，并列出「尚未进行的实板观察」。

## 已知缺口

见 `docs/hardware/board.md` 的「未知与冲突记录」与 `PROGRESS.md` 顶部。
