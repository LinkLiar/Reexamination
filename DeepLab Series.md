膨胀卷积：不降低分辨率
空间敏感度：fully-connected CRF(Conditional Random Field)耗时
DCNNs(Deep Covolutional Neural Netsworks)
MSc(Multi-Scale):原图+四个maxpooling了，增加训练参数数量，占用GPU，降低推理速度
LargeFOV减少训练参数，提升训练速度

空洞卷积优势：
图像分割种需要较大感受野来更好完成任务
没有引入额外的参数

3个 3*3  滑动步长为1
感受野为 7*7
1个 7*7  滑动步长为1
感受野为 7*7
参数量 27 : 49

SPP-Layer:
为了使网络模型去适应不同尺寸的图片
全连接层限制输入大小
不管输入大小，pooling后的大小固定

ASPP = Atrous + SPP
走不同倍率的空洞卷积核 出 卷积图
然后 叠起来，然后1**1**C 出一张特征图 

解码：等到和输入大小相同的结果