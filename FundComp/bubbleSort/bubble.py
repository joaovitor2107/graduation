def bubble(nums):
    for i in range(len(nums) - 1):
        for j in range(len(nums) - 1 - i):
            if nums[j] > nums[j + 1]:
                aux = nums[j]
                nums[j] = nums[j+1]
                nums[j+1] = aux
    return nums

def main():
    while True:
        n = int(input())
        if n == 0:
            break
        
        codigos = []
        for _ in range(n):
            aux = input().strip()
            
            if len(aux) == 4 and aux.isdigit():
                codigos.append(aux)

        bubble(codigos)
        for i in codigos:
            print(i)

main()
