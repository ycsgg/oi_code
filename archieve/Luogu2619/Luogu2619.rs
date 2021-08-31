#[allow(unused_imports)]
use std::cmp;
use std::fmt;
use std::io::stdin;

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>,
}
impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

struct Edge {
    u: i32,
    v: i32,
    w: i32,
    col: bool,
}
impl fmt::Display for Edge {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "u : {} v : {} w : {} col : {}",
            self.u, self.v, self.w, self.col
        )
    }
}

mod dsu {
    pub struct DSU {
        fa: Vec<usize>,
    }
    impl DSU {
        pub fn init(&mut self, n: usize) {
            self.fa = (0..n).collect();
        }
        pub fn find(&mut self, x: usize) -> usize {
            if x == self.fa[x] {
                return x;
            } else {
                self.fa[x] = self.find(self.fa[x]);
                return self.fa[x];
            }
        }
        pub fn merge(&mut self, x: usize, y: usize) {
            let fx = self.find(x);
            let fy = self.find(y);
            if fx == fy {
                return;
            }
            self.fa[fx] = fy;
        }
        pub fn new() -> DSU {
            DSU {
                fa: Vec::<usize>::new(),
            }
        }
    }
}

fn check(k: i32, dsu: &mut dsu::DSU, graph: &mut Vec<Edge>, n: i32) -> (i32, i32) {
    for e in graph.iter_mut() {
        if e.col == true {
            e.w += k;
        }
    }
    dsu.init(n as usize);
    graph.sort_by(|a, b| {
        if a.w == b.w {
            if (a.col) {
                cmp::Ordering::Less
            } else {
                cmp::Ordering::Equal
            }
        } else if a.w < b.w {
            cmp::Ordering::Less
        } else {
            cmp::Ordering::Greater
        }
    });
    let mut cnt = 0;
    let mut tot = 0;
    let mut sum = 0;
    for e in graph.iter() {
        if cnt == n - 1 {
            break;
        }
        let x = dsu.find(e.u as usize);
        let y = dsu.find(e.v as usize);
        if x == y {
            continue;
        }
        dsu.merge(x, y);
        cnt += 1;
        if e.col {
            tot += 1;
        }
        sum += e.w;
    }
    for e in graph.iter_mut() {
        if e.col == true {
            e.w -= k;
        }
    }
    (tot, sum)
}

fn main() {
    let mut scan = Scanner::default();

    let n = scan.next::<i32>();
    let m = scan.next::<i32>();
    let need = scan.next::<i32>();

    let mut dsu = dsu::DSU::new();
    let mut graph: Vec<Edge> = Vec::new();

    for _ in 0..m {
        graph.push(Edge {
            u: scan.next::<i32>(),
            v: scan.next::<i32>(),
            w: scan.next::<i32>(),
            col: scan.next::<i32>() == 0,
        });
    }
    let mut l: i32 = -111;
    let mut r: i32 = 111;
    let mut ans: i32 = 0;
    while l <= r {
        let mid: i32 = (l + r) / 2;
        let res = check(mid, &mut dsu, &mut graph, n);
        if res.0 >= need {
            l = mid + 1;
            ans = res.1 - need * mid;
        } else {
            r = mid - 1;
        }
    }
    println!("{}", ans);
}