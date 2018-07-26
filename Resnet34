from torch import nn
import torch as t

from torch.nn import functional as F


class ResidualBlock(nn.Module):
    def __init__(self, in_channel, out_channel, stride=1, shortcut=None):
        super(ResidualBlock, self).__init__()
        self.left = nn.Sequential(
            nn.Conv2d(in_channel, out_channel, 3, stride, bias=False),
            nn.BatchNorm2d(out_channel),
            nn.ReLU(inplace=True),
            nn.Conv2d(out_channel,out_channel, 3, stride=1, padding=1, bias=False),
            nn.BatchNorm2d(out_channel)
        )

        self.right = shortcut

    def forward(self, x):
        out_left = self.left(x)
        out_right = None
        if self.right:
            out_right = self.right(x)

        out = out_left + out_right
        out = F.relu(out)
        return out


class ResNet34(nn.Module):
    def __init__(self, num_classes = 1000):
        super(ResNet34, self).__init__()
        self.pre = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=64, 7, stride=2, padding=3, bias=False),
            nn.BatchNorm2d(64),
            nn.ReLU(inplace=True),
            nn.MaxPool2d(3, stride=2, padding=1)
        )
        
        self.layer1 = self.make_layer(64, 128, block_num=3)
        self.layer2 = self.make_layer(128, 256, block_num=4, stride=2)
        self.layer3 = self.make_layer(256, 512, block_num=6, stride=2)
        self.layer4 = self.make_layer(512, 512, block_num=3, stride=2)
        
    
    def make_layer(self, in_channel, out_channel, block_num=1, stride=1):
        
        
        return 0
