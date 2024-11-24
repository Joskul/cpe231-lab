use std::io;

fn read_i32() -> i32 {
    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .expect("Failed to read line");
    line.trim().parse().expect("Failed to parse integer")
}

fn main() {
    let n = read_i32() as usize; // number of trees
    let mut p = Vec::with_capacity(n); // pot heights
    let mut t = Vec::with_capacity(n); // tree heights

    let mut h = Vec::with_capacity(n); // total heights
    let mut sum_of_diff = 0; // answer

    for _ in 0..n {
        let x = read_i32();
        p.push(x);
    }

    for _ in 0..n {
        let x = read_i32();
        t.push(x);
    }

    p.sort();
    t.sort_by(|a, b| b.cmp(a));

    for i in 0..n {
        h.push(p[i] + t[i]);
    }

    h.sort_by(|a, b| b.cmp(a));

    for i in 0..(n - 1) {
        sum_of_diff += h[i] - h[i + 1];
    }

    println!("{}", sum_of_diff);
}
