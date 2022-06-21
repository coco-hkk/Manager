# Manager
Manager Tool

# 环境
- Win 10
- Qt 6.2.4 LTS
- Qt 6.2.4 MinGW 64-bit
- Qt 6.2.4 MSVC 2019 64-bit
- minimal Qt version 6.2
- Qt Quick
- Cmake

# Cmake

1. 使用 `include` 指令引用子目录中的 CMakeLists.txt，可以将该指令理解为子目录中
   的 CMakeLists.txt 是从顶级 CMakeLists.txt 独立出部分，然后由顶级目录 inlucde
   包含回去。意味着所有的配置文件拥有共同的环境。

2. Qt 6.2.4 的 Cmake 本地化 `qt_add_translations` 需要 `Qt6::LinguistTools`。所
   以直接使用 qmake 生的成 ts 文件。

3. 将翻译文件.qm 放进 QT 的资源文件.qrc 中。

4. 使用 MSVC 2019 编译，MinGW 无法编译。
