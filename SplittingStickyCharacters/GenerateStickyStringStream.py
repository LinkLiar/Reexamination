import random
import string
import pygame
import os
import cv2

minSize = 20  # 字符串长度上限
maxSize = 20  # 字符串长度下限
generateTime = 50  # 生成多少基准字符串
imagePerString = 5 # 每个字符串生成多少种分辨率
errorPerNchar = 11  # 间接控制基准字符串错误量上限
rowPerString = 5  # 每个基准字符串生成多少错误字符串

FontsPath = r"C:\LinkDocument\FontsRestrictStream"
tempPath = r"C:\LinkDocument\tempStickyDataSetStream"
savePath = r"C:\LinkDocument\StickyDataSetStream"
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
    imgCount = 1
    for fonttype in fonttypes:
        for i in range(0, len(easySticky) - 1):
            size = random.randint(minSize, maxSize)  # 随机生成基准字符串长度
            raw = ''.join(random.sample(characters, size))
            raw = raw.replace('K', 'W')
            raw = raw.replace('k', 'w')
            raw = list(raw)
            if (i < len(easySticky)):
                raw.insert(random.randint(0, len(raw) - 1), easySticky[i])
            else:
                raw.insert(random.randint(0, len(raw) - 1), easySticky[random.randint(0,len(easySticky) - 1)])

            tempRaw = ''.join(raw)
            tempHex = ''.join([hex(ord(c)).replace('0x', '') for c in tempRaw])
            tempHex = tempHex.upper()
            i = 1

            for solution in range(0, imagePerString):
                font = pygame.font.Font(os.path.join(FontsPath, fonttype), 30 + solution*10)
                rtext = font.render(tempRaw, True, (0, 0, 0), (255, 255, 255))
                pygame.image.save(rtext, os.path.join(tempPath, tempRaw + f"+({i})" + ".png"))
                img = cv2.imread(os.path.join(tempPath, tempRaw + f"+({i})" + ".png"))
                scale_percent = 150 / img.shape[0]
                width = int(img.shape[1] * scale_percent)
                height = int(img.shape[0] * scale_percent)
                dim = (width, height)
                resized = cv2.resize(img, dim)
                resized = cv2.copyMakeBorder(resized,100,100,100,100,cv2.BORDER_CONSTANT, value=[255, 255, 255])
                cv2.imwrite(os.path.join(savePath, tempRaw + f"+({i})" + ".png"), resized)
                f.write(str(imgCount) + ',' + os.path.join(savePath, tempRaw + f"+({i})" + ".png") + ",1," + tempHex + ',' + tempRaw + ",null\n")
                i += 1
                imgCount += 1


if __name__ == '__main__':
    GenerateStickyStrings(generateTime, characters)