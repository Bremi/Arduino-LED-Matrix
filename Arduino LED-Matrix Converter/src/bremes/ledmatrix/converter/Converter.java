package bremes.ledmatrix.converter;

import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;

import javax.imageio.ImageIO;

public class Converter {

	public static void main(String[] args) {
		FileWriter fileWriter = null;
		BufferedWriter bufferedWriter = null;
		try {
			File outputFile = new File("/home/nico/badapple.txt");
			if (!outputFile.exists()) {
				outputFile.createNewFile();
			}
			fileWriter = new FileWriter(outputFile);
			bufferedWriter = new BufferedWriter(fileWriter);
			
			File[] frameFiles = new File("/media/nico/Shared/Nico/Pictures/Bad Apple Frames 8x8").listFiles();
			Arrays.sort(frameFiles);
			for (File frameFile : frameFiles) {
				BufferedImage frame = ImageIO.read(frameFile);
				System.out.println(frameFile.getName());
				for (int row = 0; row < 8; row++) {
					for (int column = 7; column >= 0; column--) {
						int argb = frame.getRGB(column, row);
						int red = (argb >> 16) & 0xff;
						int green = (argb >> 8) & 0xff;
						int blue = (argb) & 0xff;
						
						int rgbSum = red + green + blue;
						
						if (rgbSum > 254) {
							System.out.print(" ");
							bufferedWriter.write("0");
						} else {
							System.out.print("■");
							bufferedWriter.write("1");
						}
					}
					System.out.println();
					bufferedWriter.newLine();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				bufferedWriter.close();
				fileWriter.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
