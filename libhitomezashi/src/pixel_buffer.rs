use bitvec::prelude::*;
use std::fmt;
use std::ops::{Index, IndexMut};

/// 2D buffer of monochrome (white/black i.e. true/false) pixels
pub struct PixelBuffer {
    pub buffer: BitVec,
    pub width: usize,
    pub height: usize,
}

impl PixelBuffer {
    pub fn new(width: usize, height: usize) -> Self {
        let mut buffer = BitVec::with_capacity(width * height);
        buffer.resize(width * height, false);
        PixelBuffer {
            buffer,
            width,
            height,
        }
    }
    pub fn fill_rect(&mut self, x: usize, y: usize, width: usize, height: usize) {
        for i in x..(x + width) {
            for j in y..(y + height) {
                self[i].set(j, true);
            }
        }
    }
}

impl Index<usize> for PixelBuffer {
    type Output = BitSlice;

    fn index(&self, column: usize) -> &Self::Output {
        &self.buffer[(column * self.height)..((column + 1) * self.height)]
    }
}

impl IndexMut<usize> for PixelBuffer {
    fn index_mut(&mut self, column: usize) -> &mut Self::Output {
        &mut self.buffer[(column * self.height)..((column + 1) * self.height)]
    }
}

impl fmt::Display for PixelBuffer {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let mut result = String::new();
        for y in 0..self.height {
            for x in 0..self.width {
                result.push(if self[x][y] { '█' } else { ' ' })
            }
            result.push('\n')
        }
        write!(f, "{}", result)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn access_default() {
        let pixel_buffer = PixelBuffer::new(2, 3);
        assert!(pixel_buffer[0][0] == false);
    }
    #[test]
    fn mutate() {
        let mut pixel_buffer = PixelBuffer::new(2, 3);
        pixel_buffer[1].set(2, true);
        assert!(pixel_buffer[1][2] == true);
    }
    #[test]
    #[should_panic]
    fn access_out_of_bounds() {
        let pixel_buffer = PixelBuffer::new(10, 20);
        assert!(pixel_buffer[10][0] == false);
    }
    #[test]
    fn print() {
        let mut pixel_buffer = PixelBuffer::new(3, 3);
        pixel_buffer[1].set(1, true);
        let result = format!("{}", pixel_buffer);
        assert!(result == "   \n █ \n   \n");
    }
    #[test]
    fn rect() {
        let mut pixel_buffer = PixelBuffer::new(5, 3);
        pixel_buffer.fill_rect(1, 0, 2, 2);
        let result = format!("{}", pixel_buffer);
        assert!(result == " ██  \n ██  \n     \n");
    }
}
