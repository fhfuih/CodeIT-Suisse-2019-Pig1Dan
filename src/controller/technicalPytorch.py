import math
import torch
import matplotlib.pyplot as plt

torch.random.manual_seed(20493631)

y_train = torch.tensor(
    [283, 285, 287, 288, 290, 291, 291, 291, 290, 289, 287, 285, 283, 280, 278, 276, 275, 273, 273, 273, 273,
    274, 276, 277, 279, 282, 284, 286, 287, 289, 289, 290, 289, 288, 287, 285, 283, 281, 279, 276, 275, 273,
    272, 271, 271, 272, 273, 275, 277, 279, 281, 283, 285, 286, 288, 288, 288, 288, 287, 285, 283, 281, 279,
    277, 275, 273, 271, 270, 270, 270, 271, 272, 274, 276, 278, 280, 282, 284, 285, 286, 287, 287, 286, 285,
    284, 282, 279, 277, 275, 273, 271, 270, 269, 269, 269, 270, 271, 273, 275, 277],
    dtype=torch.float
)

x = torch.arange(1099, dtype=torch.float) / 1099
x_train = x[:100]
x_test = x[100:]

sine_count = 1

base = torch.randint(200, 300, (1,), dtype=torch.float, requires_grad=True)
trend = torch.randint(-100, 100, (1,), dtype=torch.float, requires_grad=True)
scale = torch.randint(5, 15, (sine_count, 1), dtype=torch.float, requires_grad=True)
period_count = torch.randint(10, 100, (sine_count, 1), dtype=torch.float, requires_grad=True)

def calc(x):
    return base + trend * x + (scale * (2 * math.pi * period_count * x)).sin().sum(0)

lr = 3e-2
epoch = 2000
optimizer = torch.optim.Adam([base, trend, scale, period_count], lr=lr)
for t in range(epoch):
    y_pred = calc(x_train)
    # print(y_pred.shape)
    loss = (y_pred - y_train).pow(2).sum()
    if t % 20 == 0:
        print(t, loss)
    optimizer.zero_grad()
    # if t < epoch-1:
    #     loss.backward(retain_graph=True)
    # else:
    #     loss.backward()
    loss.backward()
    optimizer.step()

print(sine_count, base, trend, scale, period_count)

fig = plt.figure()
fig.set_size_inches(16, 4)

xt = x_train.numpy()
yt = y_train.numpy()
yte = calc(x_train).detach().numpy()
xe = x_test.numpy()
yee = calc(x_test).detach().numpy()

plt.plot(xt, yt)
plt.plot(xt, yte)
plt.plot(xe, yee)
plt.show()
