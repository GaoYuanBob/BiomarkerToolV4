# BiomarkerTool-V4
海马体标注工具，读取TIFF（.tif / .tiff）数据并进行标注。也可读取之前的标注等信息。\
使用 VS2017 + Qt-5.12 编写。\
需要安装TIFF的库，在VS中的 "工具" --> "NuGet包管理器" --> "管理解决方案的NuGet程序包" 中安装 **"libtiff"**。

## 操作方法
分为LocalView和GlobalView；\
LocalView下：\
&emsp;&emsp;可以使用加减号进行缩放，`'shift'` + `'+'` 可以进行放大，`'-'` 进行缩小（不推荐使用）。\
&emsp;&emsp;Zoomin 和 Zoomout 功能可以实现方法两倍和还原功能。\
&emsp;&emsp;使用滚轮可以进行缩放，最多缩小8倍，最小就是默认状态，即为和TIFF图像同样的分辨率。

GloabalView下：\
&emsp;&emsp;目前没有缩放功能。

左下角的小图在两种view下不变，都是显示整个图像。点击小图像中的方块可以直接在大视图中定位到目标方块区域。在LocalView下直接切换，在GlobalView下不会切换，但是换到LocalView就切换到选择的区域了。

选取区域使用鼠标右键，可以进行方块选取以及自由选取。

## .dll and .lib Needed
for libtiff（安装libtiff之后生成）\
&emsp;&emsp;Debug:\
&emsp;&emsp;&emsp;&emsp;jpeg.dll\
&emsp;&emsp;&emsp;&emsp;libtiff.dll\
&emsp;&emsp;&emsp;&emsp;zlibd.dll\
&emsp;&emsp;&emsp;&emsp;libtiffd.lib\
&emsp;&emsp;Release:\
&emsp;&emsp;&emsp;&emsp;jpeg.dll\
&emsp;&emsp;&emsp;&emsp;libtiff.dll\
&emsp;&emsp;&emsp;&emsp;zlib.dll\
&emsp;&emsp;&emsp;&emsp;libtiff.lib

## 参考资料
1. Using the TIFF Library：http://www.libtiff.org/libtiff.html#Mman \
根据TIFF数据存储方式的不同，的I/O有三种方式：\
&emsp;&emsp;1）Scanline-based Image I/O：调用 TIFFReadScanline\
&emsp;&emsp;2）Strip-oriented Image I/O：调用 TIFFReadEncodedStrip\
&emsp;&emsp;3）Tile-oriented Image I/O：调用 TIFFReadTile\
目前只支持第二种。
2. TIFF Tag 含义: https://www.awaresystems.be/imaging/tiff/tifftags/baseline.html

## 可能的问题
1. 目前只支持压缩方式为**不压缩**的，即 `TIFFGetField(tif, TIFFTAG_COMPRESSION, &imageCompression);` 读取出来的 `imageCompression` 只能是1。（因为目前读取方式为：TIFFReadEncodedStrip，只能读取）
2. GlobalView据绘制窗口的比例和图像比例的关系，对长或者宽进行裁剪，所以会出现右边有一部分LocalView画面的情况
