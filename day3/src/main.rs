use std::{
    collections::HashSet,
    fs::File,
    io::{self, BufRead},
    path::Path,
};

fn get_priority(item: &char) -> u32 {
    let item = *item as u32;

    if item > 96 {
        return item - 96;
    } else {
        return item - 38;
    }
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn main() {
    if let Ok(lines) = read_lines("./input") {
        let mut result: u32 = 0;

        let lines: Vec<String> = lines.map(|l| l.unwrap()).collect();

        for group in lines.chunks(3) {
            let group: Vec<HashSet<char>> = group
                .iter()
                .map(|items| HashSet::<char>::from_iter(items.chars()))
                .collect();

            let first_elf = group.first().unwrap();

            for item in first_elf {
                if group.len() == group.iter().filter(|items| items.contains(item)).count() {
                    result += get_priority(item);
                }
            }
        }

        println!("{}", result);
    }
}
