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
    if let Ok(lines) = read_lines("./input") {
        let lines: Vec<String> = lines.map(|l| l.unwrap()).collect();

        let board: Vec<Vec<String>> = lines
            .clone()
            .into_iter()
            .filter(|l| l.contains("["))
            .map(|l| {
                l.chars()
                    .collect::<Vec<char>>()
                    .chunks(4)
                    .map(|c| c.iter().collect::<String>())
                    .collect()
            })
            .collect();

        let mut stacks: Vec<Vec<String>> = vec![];

        for row in board {
            for (col, value) in row.iter().enumerate() {
                if stacks.len() < col + 1 {
                    stacks.push(Vec::<String>::new());
                }

                if value.trim().chars().count() > 0 {
                    stacks[col].push(value.trim().to_owned());
                }
            }
        }

        lines
            .clone()
            .into_iter()
            .filter(|l| l.contains("move"))
            .for_each(|operation| {
                let mut parts = operation.split_whitespace().map(|s| s.parse::<usize>());
                match (
                    parts.next(),
                    parts.next(),
                    parts.next(),
                    parts.next(),
                    parts.next(),
                    parts.next(),
                ) {
                    (
                        Some(Err(_)),
                        Some(Ok(count)),
                        Some(Err(_)),
                        Some(Ok(from)),
                        Some(Err(_)),
                        Some(Ok(to)),
                    ) => {
                        let mut new_items: Vec<String> =
                            stacks.get_mut(from - 1).unwrap().drain(0..count).collect();

                        let mut old_items = stacks.get(to - 1).unwrap().clone();

                        // wipe the original stack
                        stacks.get_mut(to - 1).unwrap().clear();

                        // reconstruct items
                        stacks.get_mut(to - 1).unwrap().append(&mut new_items);
                        stacks.get_mut(to - 1).unwrap().append(&mut old_items);

                        dbg!(&stacks);
                    }
                    _ => {} // ignore invalid input
                }
            });

        let mut msg = String::from("");
        for stack in stacks {
            msg.push_str(stack.first().unwrap());
        }

        dbg!(msg);
    }
}
