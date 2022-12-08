use std::{
    collections::HashMap,
    fs::File,
    io::{self, BufRead},
    path::{self, Path},
};

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where
    P: AsRef<Path>,
{
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn line_to_target_path(line: &str) -> String {
    line.replace("$ cd ", "")
}

fn construct_current_path(current_path: &str, target_path: &str) -> String {
    let last_slash = current_path.rfind("/").unwrap_or(current_path.len());

    let mut new_path = String::from(current_path);

    if target_path != ".." {
        if target_path == "/" {
            new_path = target_path.to_owned();
        } else {
            if current_path == "/" {
                new_path = format!("/{}", target_path);
            } else {
                new_path = format!("{}/{}", current_path, target_path);
            }
        }
    } else {
        new_path.replace_range(last_slash..current_path.len(), "");

        if new_path == "" {
            new_path = "/".to_owned();
        }
    }

    return new_path;
}

fn main() {
    let mut dir_map: HashMap<String, u64> = HashMap::new();

    if let Ok(lines) = read_lines("./input") {
        let lines: Vec<String> = lines.map(|l| l.unwrap()).collect();

        // "state"
        let mut current_path: String = format!("");

        for line in lines {
            // If changing directory
            if line.starts_with("$ cd ") {
                let target_path = line_to_target_path(&line);

                current_path = construct_current_path(&current_path, &target_path);
            } else {
                let line_segments: Vec<&str> = line.split_whitespace().collect();

                // If size entry is found
                if let Ok(size) = line_segments.get(0).unwrap().parse::<u64>() {
                    // increment entries for the current path and all the ancestors
                    let mut path_segments: Vec<&str> = current_path.split("/").collect();
                    // dbg!(&current_path);
                    // dbg!(&path_segments);

                    if current_path == "/" {
                        path_segments = vec![""];
                    }

                    let mut path_key = String::new();

                    for p in path_segments {
                        path_key = format!("{}/{}", path_key, p);

                        if !dir_map.contains_key(&path_key) {
                            dir_map.insert(path_key.clone(), size);
                        } else {
                            let current_size = dir_map.get_mut(&path_key).unwrap();
                            *current_size = *current_size + size;
                        }
                    }
                }
            }
        }

        let used_space = dir_map.get("/").unwrap();

        println!("used space: {}", used_space);

        let available = 70000000 - used_space;

        println!("available: {}", available);

        // minimum amount of bytes to free
        let to_free = 30000000 - available;

        println!("to free: {}", to_free);

        let mut matching_directories: Vec<u64> = dir_map
            .iter()
            .filter(|p| p.1 > &to_free)
            .map(|p| p.1.to_owned())
            .collect();

        matching_directories.sort();

        // result
        dbg!(matching_directories.first());
    }
}
