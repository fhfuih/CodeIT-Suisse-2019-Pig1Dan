import sys
import itertools
import numpy as np
import time
# import matplotlib.pyplot as plt

def raodong(T, base, trend, scales, pcounts):
    if T > 1e5:
        T = 1e5
    if T < 0:
        T = 0
    T = T / 1e3
    b = (np.random.random() - 0.5) * T * 200 + base
    b = min(max(b, 200), 300)
    t = (np.random.random() - 0.5) * T * 400 + trend
    t = min(max(t, -100), 100)
    scales = (np.random.random() - 0.5) * T * 20 + scales
    scales = np.minimum(np.maximum(scales, 5), 15)
    pcounts = (np.random.random() - 0.5) * T * 180 + pcounts
    pcounts = np.minimum(np.maximum(pcounts, 10), 100)
    return b, t, scales, pcounts

def calc(t, base, trend, scales, pcounts):
    return base + trend * t + np.sum(scales * np.sin(2 * np.pi * pcounts * t), axis=0)

def calcc(t, base, trend, scale, pc):
    return base + trend * t + scale * np.sin(2 * np.pi * pc * t)

def trade(y, offset=100):
    cash = 1
    hold = y[0]
    strategy = [offset]
    for i in range(1, len(y)-1):
        if hold and y[i] >= y[i-1] and y[i] > y[i+1]:
            cash = cash / hold * y[i]
            hold = None
            strategy.append(i + offset)
        elif hold is None and y[i] <= y[i-1] and y[i] < y[i+1]:
            hold = y[i]
            strategy.append(i + offset)
    if hold is not None:
        cash = cash / hold * y[-1]
        hold = None
        strategy.append(len(y)-1+offset)
    return cash, strategy

def y_score(y_pred, y_real):
    final_cash, _ = trade(y_pred)
    max_final_cash, _ = trade(y_real)
    return max(0, (final_cash - 1) / (max_final_cash - 1))

def param_score(base, trend, scales, pcounts, t, y):
    y_pred = calc(t, base, trend, scales, pcounts)
    return np.sum(np.abs(y_pred - y))

def SA(t, y, sine_count):
    base = np.random.randint(200, 300)
    trend = np.random.randint(-100, 100)
    scales = np.random.randint(5, 15, (sine_count, 1))
    pcounts = np.random.randint(10, 100, (sine_count, 1))

    best_base = 0
    best_trend = 0
    best_scales = 0
    best_pcounts = 0

    if sine_count == 1:
        T = 1e4
        coef = 0.997
        T_min = 1e-3
    elif sine_count == 2:
        T = 1e4
        coef = 0.9993
        T_min = 1e-3
    elif sine_count == 3:
        T = 1e3
        coef = 0.9996
        T_min = 1e-4
    else:
        T = 1e3
        coef = 0.9999
        T_min = 1e-4

    score_now = param_score(base, trend, scales, pcounts, t, y)
    start = time.time()
    counter = 0

    best_score = score_now

    while T > T_min:

        if T < 1:
            coef = 0.9999

        # print(T)
        if time.time() - start > 6:
            break

        new_set = raodong(T * 1.0, base, trend, scales, pcounts)
        new_score = param_score(*new_set, t, y)
        delta = new_score - score_now

        if delta < 0 or np.exp(-delta / T) > np.random.random():

            base, trend, scales, pcounts = new_set
            score_now = new_score

            if new_score < best_score:
                best_score = new_score
                (best_base, best_trend, best_scales, best_pcounts) = new_set


        T *= coef

    return best_base, best_trend, best_scales, best_pcounts


def brute(t, y_real, sine_count):
    max_score = 0
    mbase = None
    mtrend = None
    mscales = None
    mpc = None
    for base in range(200, 300, 10):
        for trend in range(-100, 100, 10):
            for scales in itertools.product(range(5, 15), repeat=sine_count):
                for pcounts in itertools.product(range(10, 100), repeat=sine_count):
                    y_pred = calc(
                        t,
                        base,
                        trend,
                        np.asarray(scales),
                        np.asarray(pcounts))
                    cur_score = y_score(y_pred, y_real)
                    if cur_score > max_score:
                        max_score = cur_score
                        mbase = base
                        mtrend = trend
                        mscales = np.asarray(scales)
                        mpc = np.asarray(pcounts)
    return mbase, mtrend, mscales, mpc, max_score

# x_train = np.arange(30) / 90
# y_train = [241, 242, 243, 244, 244, 245, 246, 246, 246, 246, 246, 246, 245, 245, 244, 244, 243, 243, 242, 242, 241, 241,
#     241, 242, 242, 243, 244, 244, 245, 246]
# y_test = [248.0237288698771, 249.08090060113744, 250.08826187106925, 251.01083737788557, 251.8174407897403,
#     252.4820684229782, 252.98506131430463, 253.31398375532103, 253.46417902881325, 253.43897751163246,
#     253.24954784430986, 252.91439781844994, 252.4585472866212, 251.91241005636977, 251.3104347351166,
#     250.6895652648834, 250.08758994363023, 249.5414527133788, 249.0856021815501, 248.75045215569014,
#     248.56102248836754, 248.53582097118675, 248.68601624467897, 249.01493868569537, 249.5179315770218,
#     250.1825592102597, 250.98916262211443, 251.91173812893075, 252.91909939886256, 253.97627113012288,
#     255.0460520535713, 256.0906774110047, 257.0735066150713, 257.96066067139145, 258.72253618853586,
#     259.3351283166435, 259.7811034942037, 260.050574063288, 260.1415401366431, 260.05997897015624,
#     259.81957784674927, 259.4411224087867, 258.9515677736589, 258.38283394322565, 257.7703793387695,
#     257.1516162084004, 256.56423872037846, 256.0445384577765, 255.62578259292454, 255.33672721899555,
#     255.20033227608943, 255.2327355001637, 255.44253124775366, 255.8303864249044, 256.3890106839719,
#     257.1034822201611, 257.95191460835974, 258.90643488016235, 259.9344291320425, 261.0]
if __name__ == '__main__':
    filename = sys.argv[1]
    with open(filename) as fp:
        command = fp.read()


    t_train = np.arange(100) / 1099
    t_test = np.arange(100, 1100) / 1099

    inp = eval(command)
    out = []
    for i, y_train in enumerate(inp):
        sine_count = i + 1
        params = SA(t_train, y_train, sine_count)
        y_test_pred = calc(t_test, *params)
        _, stretegy = trade(y_test_pred, 100)
        out.append(stretegy)
    print(out)
