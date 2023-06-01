use bitvec::prelude::*;
use clap::Parser;
use libhitomezashi as hitomezashi;
use std::process::ExitCode;

#[derive(Parser, Debug)]
#[command(author, version, about)]
struct Args {
    #[arg(short = 'x', long, value_parser = validate_xy_pattern)]
    x_pattern: BitVec,
    #[arg(short = 'y', long, value_parser = validate_xy_pattern)]
    y_pattern: BitVec,
    #[arg(short = 'g', long)]
    gap: usize,
    #[arg(short = 'l', long)]
    line_thickness: usize,
    #[arg(short = 'f', long, value_parser = parse_rgb_str)]
    foreground_colour: image::Rgb<u8>,
    #[arg(short = 'b', long, value_parser = parse_rgb_str)]
    background_colour: image::Rgb<u8>,
    #[arg(short = 'o', long)]
    output_path: String,
}

fn validate_xy_pattern(pattern_raw: &str) -> Result<BitVec, String> {
    let mut result = BitVec::new();
    for ch in pattern_raw.chars() {
        if ch == '1' {
            result.push(true);
        } else if ch == '0' {
            result.push(false);
        } else {
            return Err(String::from("must consist of only 0 and 1"));
        }
    }
    Ok(result)
}

fn parse_rgb_str(rgb_str: &str) -> Result<image::Rgb<u8>, String> {
    let rgb: csscolorparser::Color = match csscolorparser::parse(rgb_str) {
        Ok(rgb) => rgb,
        Err(e) => return Err(e.to_string())
    };
    Ok(image::Rgb::from([(rgb.r * u8::MAX as f64) as u8, (rgb.g * u8::MAX as f64) as u8, (rgb.b * u8::MAX as f64) as u8]))
}

fn main() -> ExitCode {
    let args = Args::parse();

    let pattern = hitomezashi::get_hitomezashi_pattern(
        args.x_pattern,
        args.y_pattern,
        args.gap,
        args.line_thickness,
    );
    let mut image = image::RgbImage::new(pattern.width as u32, pattern.height as u32);
    for x in 0..pattern.width {
        for y in 0..pattern.height {
            image.put_pixel(x as u32, y as u32, if pattern[x][y] {args.foreground_colour} else {args.background_colour})
        }
    }
    match image.save_with_format(&args.output_path, image::ImageFormat::Png) {
        Ok(_) => ExitCode::SUCCESS,
        Err(e) => {
            eprintln!("error: failed to save output image to {}: {}", args.output_path, e);
            ExitCode::FAILURE
        }
    }
}
