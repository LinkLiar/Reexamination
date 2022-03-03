import random
import string
import pygame
import os
import cv2

minSize = 18  # 字符串长度上限
maxSize = 18  # 字符串长度下限
generateTime = 30  # 生成多少基准字符串
errorPerNchar = 11  # 间接控制基准字符串错误量上限
rowPerString = 5  # 每个基准字符串生成多少错误字符串

FontsPath = r"D:\LinkDocument\FontsRestrict"
tempPath = r"C:\LinkDocument\temp"
savePath = r"C:\LinkDocument\StickyDataSet"
fonttypes = os.listdir(FontsPath)

easySticky = [
    "xw", "wx", "wy", "yw", "wr", "rw", "wn", "wu", "uw", "iw", "wi", "kw",
    "vm", "wm", "vw", "wv", "rx", "xr", "rv", "vr", "ry", "yr", "ru", "xy",
    "yx", "xv", "vx", "rn", "rri", "vv"
]

pygame.init()
characters = string.ascii_uppercase + string.ascii_lowercase  # + string.digits    # 字符集 = 大写 + 数字 + 小写

txtName = os.path.join(savePath, "answer.txt")
f = open(txtName, 'w')


def GenerateStickyStrings(count, char):
    for i in range(0, count):
        size = random.randint(minSize, maxSize)  # 随机生成基准字符串长度
        raw = ''.join(random.sample(characters, size))
        raw = list(raw)
        raw.insert(random.randint(0, len(raw) - 1), easySticky[i - 1])
        tempRaw = ''.join(raw)
        i = 1
        for fonttype in fonttypes:
            font = pygame.font.Font(os.path.join(FontsPath, fonttype), 30)
            rtext = font.render(tempRaw, True, (0, 0, 0), (255, 255, 255))
            pygame.image.save(
                rtext, os.path.join(tempPath, tempRaw + f"+({i})" + ".png"))
            img = cv2.imread(
                os.path.join(tempPath, tempRaw + f"+({i})" + ".png"))
            scale_percent = 200  # percent of original size
            width = int(img.shape[1] * scale_percent / 100)
            height = int(img.shape[0] * scale_percent / 100)
            dim = (width, height)
            resized = cv2.resize(img, dim)
            cv2.imwrite(os.path.join(savePath, tempRaw + f"+({i})" + ".png"),
                        resized)
            i += 1
            f.write(
                os.path.join(savePath, tempRaw + f"+({i})" + ".png") + ',' +
                tempRaw + "\n")


if __name__ == '__main__':
    GenerateStickyStrings(generateTime, characters)