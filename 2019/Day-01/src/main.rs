fn main() {
    let ans: u32 = include_str!("../../Data/01_data.txt")
        .lines()
        .map(|line| {
            let mass = line.parse::<u32>().unwrap();
            let fuel = (mass / 3) - 2;
            fuel
        })
        .fold(0, |acc, v| { return acc + v });

        println!("{}", ans);
}
