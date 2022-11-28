class ElGamal {
    constructor(p = 257, g = 8, k = 4) {
        this.p = p
        this.g = g
        this.k = k
        this.a = Math.pow(g, k) % p
    }

    cipher(key_close, clear_list) {
        // console.log('---------cipher----------------');
        // console.log(`key_close ${key_close}`);
        // console.log(`clear_list ${clear_list}`);
        // console.log('----------------------------');
        const key_open = this.pow(this.g, key_close) % BigInt(this.p)
        // const key_open = Math.pow(this.g, key_close) % this.p

        const b_list = clear_list.map(item => BigInt(this.pow(key_open, this.k) * BigInt(item) % BigInt(this.p)))
        // const b_list = clear_list.map(item => BigInt(Math.pow(key_open, this.k) * item % this.p))
        return [key_open, b_list]
    }

    pow(N, s) {
        const n = N
        N = BigInt(N)
        for (let i = 1; i < s; i++) N *= BigInt(n)
        return N
    }

    decipher(key_close, ctext_list) {
        // console.log('---------decipher----------------');
        // console.log(`key_close ${key_close}`);
        // console.log(`clear_list ${ctext_list}`);
        // console.log(`test ${ctext_list[0] * Math.pow(this.a, this.p - 1 - key_close) % this.p}`);
        // console.log('----------------------------');
        // console.log(this.pow(this.a, this.p - 1 - key_close));
        const key_open = Math.pow(this.g, key_close) % this.p
        return [key_open, ctext_list.map(item => BigInt((BigInt(this.pow(this.a, this.p - 1 - key_close)) * BigInt(item)) % BigInt(this.p)))]
        // return [key_open, ctext_list.map(item => BigInt((BigInt(Math.pow(this.a, this.p - 1 - key_close)) * BigInt(item)) % BigInt(this.p)))]
    }
}

module.exports.ElGamal = ElGamal

// var gamal = new ElGamal()
// const res_cipher = gamal.cipher(11, [120])
// console.log(`res_cipher ${res_cipher[1]}`);
// console.log('---------------------------------------------------');
// const res_decipher = gamal.decipher(11, res_cipher[1])
// console.log(`res_decipher ${res_decipher[1]}`);