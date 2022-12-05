use std::{
    fs::File,
    io::{self, BufRead},
    path::Path,
};

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn main() {
    if let Ok(lines) = read_lines("./calories") {
        let mut chunks = Vec::<Vec<i64>>::new();
        let mut buffer = Vec::<i64>::new();

        for line in lines {
            if let Ok(item) = line {
                if !item.is_empty() {
                    buffer.push(item.parse().unwrap());
                } else {
                    if buffer.len() > 0 {
                        chunks.push(buffer.to_owned());
                        buffer.clear();
                    }
                }
            }
        }

        let mut summed: Vec<i64> = chunks.iter().map(|item| item.iter().sum::<i64>()).collect();

        summed.sort();
        summed.reverse();

        dbg!(summed.iter().take(3).sum::<i64>());
    }
}
