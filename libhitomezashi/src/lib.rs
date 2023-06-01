mod pixel_buffer;
use bitvec::prelude::*;
use pixel_buffer::PixelBuffer;

pub fn get_hitomezashi_pattern(
    x_pattern: BitVec,
    y_pattern: BitVec,
    gap: usize,
    line_thickness: usize,
) -> PixelBuffer {
    let mut buf = PixelBuffer::new(x_pattern.len() * gap, y_pattern.len() * gap);
    // Draw y pattern (horizontal) lines
    for i in 0..y_pattern.len() {
        for j in 0..x_pattern.len() {
            if (j % 2 != 0) == y_pattern[i] {
                let x = j * gap;
                let y = i * gap;
                let width = gap;
                let height = line_thickness;
                buf.fill_rect(x, y, width, height);
            }
        }
    }
    // Draw x pattern (vertical) lines
    for i in 0..x_pattern.len() {
        for j in 0..y_pattern.len() {
            if (j % 2 != 0) == x_pattern[i] {
                let x = i * gap;
                let y = j * gap;
                let width = line_thickness;
                let height = gap;
                buf.fill_rect(x, y, width, height)
            }
        }
    }

    // Join up the lines to avoid leaving holes at the intersections
    // The best way to understand how this works is to try commenting it out
    for x in (gap..buf.width).step_by(gap) {
        for y in (gap..buf.height).step_by(gap) {
            let width = line_thickness;
            let height = line_thickness;
            buf.fill_rect(x, y, width, height);
        }
    }
    buf
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test() {
        let x_pattern = bitvec![1, 1, 0, 1, 1, 1];
        let y_pattern = bitvec![0, 1, 1, 0, 0, 0];
        let result = format!("{}", get_hitomezashi_pattern(x_pattern, y_pattern, 3, 1));
        println!("{}", result);
        assert!(result == "███   ███   ███   \n      █           \n      █           \n█  ████  ████  ███\n█  █     █  █  █  \n█  █     █  █  █  \n   ████  ████  ███\n      █           \n      █           \n████  ████  ████  \n█  █     █  █  █  \n█  █     █  █  █  \n████  ████  ████  \n      █           \n      █           \n████  ████  ████  \n█  █     █  █  █  \n█  █     █  █  █  \n")
    }
}
