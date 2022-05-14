自组织增量学习神经网络

余航，上海大学讲师，上海市海外高层次人才，长期从事不确定环境下的计算智能相关研究。以第一作者身份发表 SCI/EI 论文 15 篇，其中包括中科院一区期刊IEEE-TNNLS、 IEEE-TFS、IEEE-TCYB和CCF推荐的A类期刊IEEE-TKDE等。并且，长期担任IEEE TNNLS、IEEE TCYB等多个 IEEE 汇刊的审稿人，以及IJCAI、IJCNN等国际顶级会议的审稿人。此外，主持并参与多项军工项目，并入选上海市启明星培养专项-扬帆计划。

1.流式大数据计算与应用研究
2.机器学习方法研究，主要涉及增量学习，小样本学习，以及深度学习
3.计算智能方法研究，主要涉及模糊学习和进化学习
4.概念漂移和异常检测
5.知识图谱方法、实践与应用
6.目标检测

报告题目：概念漂移的检测、理解、适应
报告摘要：概念漂移描述了数据流随时间的变化，其潜在数据分布也发生了不可预知的变化。这种潜在数据分布发生变化，导致从历史数据学习到的模型已不再适用新的数据流，从而引起学习模型表现的下降，大量的数据分析已经揭示了数据流环境下的机器学习如果不考虑漂移的话会导致很差的学习结果。基于该原因，大量关于概念漂移的研究方法被提出，而这些方法主要集中在概念漂移的检测，理解和适配。漂移的检测主要指何时发现数据流潜在数据分布的变化，解决when的问题，漂移的理解主要指如何识别数据流潜在数据分布变化的方式，解决how的问题，漂移的适配是指知道何时发生概念漂移，以及如何发生概念漂移后，该怎样调整模型，使得模型能够适应新的潜在分布，解决learn的问题。为了帮助研究者们定义哪些研究课题是重要的以及如何在数据分析中使用相关技术，本次报告将会就概念漂移检测、理解和适配的方法技术进行分享。

Real-Time Prediction System of Train Carriage Load Based on Multi-Stream Fuzzy Learning
https://ieeexplore.ieee.org/document/9678130

MORStreaming: A Multioutput Regression System for Streaming Data
https://ieeexplore.ieee.org/document/9526914

Topology Learning-based Fuzzy Random Neural Network for Streaming Data Regression
https://ieeexplore.ieee.org/document/9265257

Continuous Support Vector Regression for Nonstationary Streaming Data
https://ieeexplore.ieee.org/document/9194301

An Online Robust Support Vector Regression for Data Streams
https://ieeexplore.ieee.org/document/9034023

Online Topology Learning by a Gaussian Membership-Based Self-Organizing Incremental Neural Network
https://ieeexplore.ieee.org/document/8897716

# 笔记：
概念漂移应用可以根据五个评估指标分为监控任务、决策、援助信息以及AI和机器人四个方面。
这五个指标分别是学习速度、分类和预测精度、误分类惩罚、实际标签和不利活动。

## 数据漂移
目前有很多广泛存在的数据，像金融数据、交通数据等，这类数据不同于传统的静态数据(Static Data)，而是作为一种数据量大、实时性强的流式数据(Data Stream)而存在。
流式数据分为稳定的数据流和动态的数据流，稳定的数据流具有稳定独立同分布的特点，而动态数据流则是不独立同分布的，所以会产生概念漂移的现象。
sudden指的是迅速同时又不可逆的改变，强调的是发生的迅速。
incremental和gradual都是强调改变发生的缓慢：
incremental强调值的随时间改变，
gradual则是数据分布的改变。
也有些研究者将这两种变化划分为同一类，用incremental gradual这个术语来代替。
recurring则是一种temporary（临时性）的改变，在一段短时间内会恢复之前的状态。所以也有些研究者将其称为local drift，它不具有周期性，是在不规则的时间间隔内反复转换。
blip是代表一种很稀少的事件，它可以被视为一种anomaly或者outlier（异常）。
noise是一种随机的改变，通常这种数据会从样本数据中filter out。

## 概念漂移
概念漂移是一种现象，即目标领域的统计属性随着时间的推移以一种任意的方式变化。

# 概念
从广义上讲，模型有两种衰变方式：
在数据漂移的情况下，数据随着时间的推移而发展，可能引入先前看不见的各种数据及其所需的新类别，但是对先前标记的数据没有影响。
在概念漂移的情况下，即使数据的一般分布没有变化，我们对数据的解释也会随时间而变化。这使得最终用户将模型预测解释为随着时间的推移，对于相同/相似的数据已经恶化。此处的修复需要重新标记受影响的旧数据并重新训练模型。数据和概念都可以同时漂移，使问题更加棘手。

如果我们诊断概念漂移，受影响的旧数据也需要重新标记并重新训练模型
如果我们诊断数据漂移，则需要标记足够的新数据以引入新类并重新训练模型
综合以上几点，我们发现数据和概念都发生了漂移

# 线上汇报
黑盒 识别与定位 概念漂移 