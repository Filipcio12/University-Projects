export class Fib {
    index: bigint;
    value: bigint;

    constructor(index: bigint) {
        this.index = index;
        this.value = Fib.calcFib(index);
    }

    static calcFib(n: bigint): bigint {
        if (n <= 1) {
            const res = BigInt(n);
            return res;
        }
        let fib: bigint = 1n;
        let prevFib: bigint = 1n;

        for (let i: bigint = 2n; i < n; i += 1n) {
            let temp: bigint = fib;
            fib += prevFib;
            prevFib = temp;
        }
        return fib;
    }
}