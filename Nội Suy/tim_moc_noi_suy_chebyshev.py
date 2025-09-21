import numpy as np

# Nhập input: a, b (b > a), n là bậc đa thức nội suy
a = float(input("Nhap a: "))
b = float(input("Nhap b: "))
n = int(input("Nhap n: "))

# Bước 1: Khởi tạo mảng res
res = []

# Bước 2: Vòng lặp từ i = 0 đến n 
for i in range(n + 1):
    # Công thức Chebyshev:
    cos_value = np.cos((2 * i + 1) * np.pi / (2 * (n + 1)))
    x = (a + b) / 2 + (b - a) / 2 * cos_value

    res.append(float(x))

# Bước 3: In kết quả
output = "Cac moc noi suy Chebyshev toi uu tren doan [{}, {}]:\n{}".format(a, b, res)
for i in res:
    print(f"{i:.6f}", end=" ")