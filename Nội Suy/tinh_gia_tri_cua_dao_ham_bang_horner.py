from math import factorial

def horner_modified(coeffs, c, k):
    n = len(coeffs) - 1
    b = [0] * (n + 1)

    b[n] = coeffs[n]
    for i in range(n - 1, -1, -1):
        b[i] = b[i + 1] * c + coeffs[i]

    results = {"P(c)": b[0]}

    for i in range(1, k + 1):
        for j in range(n - 1, i - 1, -1):
            b[j] = b[j + 1] * c + b[j]
        results[f"P({i})(c)"] = factorial(i) * b[i]

    return results

if __name__ == "__main__":
    # P(x) = 2x^3 - 6x^2 + 2x - 1
    coeffs = [-1, 2, -6, 2]  # a0 = -1, a1 = 2, a2 = -6, a3 = 2
    c = 3
    k = 3

    result = horner_modified(coeffs, c, k)
    for key, val in result.items():
        print(f"{key} = {val}")