# ====================
# 学習サイクルの実行
# ====================

# パッケージのインポート
from dual_network import dual_network
from self_play import self_play
from train_network import train_network
from evaluate_network import evaluate_network
import time

# デュアルネットワークの作成
dual_network()

sum=0

for i in range(100):
    t_start = time.time()
    print('Train',i,'====================')
    # セルフプレイ部
    t1 = time.time()
    self_play()
    for j in range(10):
        print("セルフプレイ終了!")
    t1 = time.time() - t1

    # パラメータ更新部
    t2 = time.time()
    train_network()
    for j in range(10):
        print("パラメータ更新終了!")
    t2 = time.time() - t2

    # 新パラメータ評価部
    t3 = time.time()
    evaluate_network()
    for j in range(10):
        print("新パラメータ評価終了!")
    t3 = time.time() - t3

    
    #ターミナルでfree -h | grep "Mem:" と入力して物理メモリ量をしれる

    print("1ループの経過時間[s]:", time.time() - t_start)
    print("1回のセルフプレイ時間[s]:", t1)
    print("1回のパラメータ更新時間[s]:", t2)
    print("1回の新パラメータ評価時間[s]:", t3)