use std::collections::HashMap;

type Point = (i32, i32);

fn main() {
    let data: Vec<(Point, Point)> = include_str!("../../../Data/hydrothermal-vents-data.txt")
        .lines()
        .map(|line| {
            let strings: Vec<&str> = line.split(" -> ").collect();
            let p1: Vec<i32> = strings[0].split(',').map(|n| n.parse().unwrap()).collect();
            let p2: Vec<i32> = strings[1].split(',').map(|n| n.parse().unwrap()).collect();
            ((p1[0], p1[1]), (p2[0], p2[1]))
        })
        .collect();

    let mut sea_floor: HashMap<Point, u32> = HashMap::new();
    data.iter().for_each(|&((x1, y1), (x2, y2))| {
        if x1 == x2 {
            let bottom = if y1 < y2 { y1 } else { y2 };
            let top = if y1 > y2 { y1 } else { y2 };
            for y in bottom..=top {
                let point: Point = (x1, y);
                *sea_floor.entry(point).or_insert(0) += 1;
            }
        } else if y1 == y2 {
            let left = if x1 < x2 { x1 } else { x2 };
            let right = if x1 > x2 { x1 } else { x2 };
            for x in left..=right {
                let point: Point = (x, y1);
                *sea_floor.entry(point).or_insert(0) += 1;
            }
        } else {
            let left = if x1 < x2 { (x1, y1) } else { (x2, y2) };
            let right = if x1 > x2 { (x1, y1) } else { (x2, y2) };
            let distance = (x1 - x2).abs();
            for i in 0..=distance {
                let point: Point = (
                    left.0 + i,
                    if left.1 < right.1 {
                        left.1 + i
                    } else {
                        left.1 - i
                    },
                );
                *sea_floor.entry(point).or_insert(0) += 1;
            }
        }
    });

    let overlaps = sea_floor.values().fold(0, |sum, v| {
        if v >= &2 {
            return sum + 1;
        }

        sum
    });

    std::println!("Overlaps: {}", overlaps);
}
