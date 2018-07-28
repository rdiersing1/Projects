import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import javax.imageio.ImageIO;

import org.apache.commons.math3.complex.Complex;

public class Mandelbrot {
	static int res;
	static int heightPx;
	static int widthPx;
	static int numCycles;
	static Complex center;
	static double width;
	static double height;
	static Color startColorInside;
	static Color startColorOutside;
	static boolean colorOutside;
	static boolean colorInside;
	
	static Complex getComplex(int j, int i) {
		double icomp = (((double)i)/heightPx) * height;
		double rcomp = (((double)j)/widthPx) * width;
		icomp = (center.getImaginary() + (height/2)) - icomp;
		rcomp = (center.getReal() - (width/2)) + rcomp;
		return new Complex(rcomp, icomp);
	}
	
	static Color getMandelbrotColor(Complex c) {
		Complex curr = c;
		Set<Complex> visited = new HashSet<>();
		Color color = new Color(0, 0, 0);
		
		for (int i = 0; i < numCycles; ++i) {
			curr = curr.pow(2.0).add(c);
			if (curr.getReal() > 2.0 || curr.getImaginary() > 2.0) {
				if (colorOutside) {
					return new Color(((7*i) + startColorOutside.getRed()) % 255,
							((3*i) + startColorOutside.getGreen()) % 255, ((5*i) + startColorOutside.getBlue()) % 255);
				} else {
					return new Color(255, 255, 255);
				}
			}
			if (visited.contains(curr)) {
				if (colorInside) {
					return new Color((i + startColorInside.getRed()) % 255,
							(i + startColorInside.getGreen()) % 255, (i + startColorInside.getBlue()) % 255);
				}
				return color;
			}
			visited.add(curr);
		}
		
		return color;
	}
	
	public static void main(String[] args) throws IOException {
		
		res = 240;
		center = new Complex(-0.6, 0);
		width = 3;
		height = 3;
		numCycles = 100;
		startColorOutside = new Color(11, 11, 86);
		startColorInside = new Color(11, 11, 86);
		colorOutside = true;
		colorInside = false;
		String outputName = "Mandelbrot";
		int loadMod = 10;
		
		String configPath = "config.txt";
		if (args.length > 0) {
			configPath = args[0];
		}
		
		BufferedReader configBr = new BufferedReader(new FileReader(configPath));
		String line = null;
		while ((line = configBr.readLine()) != null) {
			if (line.startsWith("#")) continue;		// to ignore comments
			String[] lineArr = line.split(":");
			if (lineArr.length != 2) {
				System.out.println("Warning: Config file line '" + line + "' is not properly formatted");
				continue;
			}
			String command = lineArr[0].toLowerCase().trim();
			String arg = lineArr[1].toLowerCase().trim();
			
			switch (command) {
			case "resolution": res = Integer.parseInt(arg); break;
			case "center":
				String[] argArr = arg.split(",");
				center = new Complex(Double.parseDouble(argArr[0]), Double.parseDouble(argArr[1]));
				break;
			case "width": width = Double.parseDouble(arg); break;
			case "height": height = Double.parseDouble(arg); break;
			case "num_cycles": numCycles = Integer.parseInt(arg); break;
			case "start_color_outside": 
				String[] argArr1 = arg.split(",");
				startColorOutside = new Color(
						Integer.parseInt(argArr1[0]), Integer.parseInt(argArr1[1]), Integer.parseInt(argArr1[2]));
				break;
			case "start_color_inside": 
				String[] arr = arg.split(",");
				startColorInside = new Color(
						Integer.parseInt(arr[0]), Integer.parseInt(arr[1]), Integer.parseInt(arr[2]));
				break;
			case "color_outside": colorOutside = Boolean.parseBoolean(arg); break;
			case "color_inside" : colorInside = Boolean.parseBoolean(arg); break;
			case "output_name" : outputName = arg; break;
			case "load_mod" : loadMod = Integer.parseInt(arg); break;
			default: 
				System.out.print("Warning: Config file line '" + line + "' command not found");
				break;
			}
		}
		configBr.close();
		
		heightPx = res;
		widthPx = (int) ((heightPx * width) / height);
		BufferedImage set = new BufferedImage(widthPx, heightPx, BufferedImage.TYPE_INT_RGB);
				
		long start = System.nanoTime();
		
		for (int i = 0; i < heightPx; ++i) {
			for (int j = 0; j < widthPx; ++j) {
				Complex currLoc = getComplex(j, i);
				set.setRGB(j, i, getMandelbrotColor(currLoc).getRGB());
			}
			if (i % loadMod == 0) {
				System.out.println(String.format("%.2f", (100 * (double)i/heightPx)) + "%   \r");
			}
		}
		
		long end = System.nanoTime();
		
		System.out.print("runtime: " + ((double)(end - start)/1_000_000_000) + "sec");
		
		DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
		Date now = new Date();
		File outFile = new File("rsc/" + outputName + dateFormat.format(now) + ".png");
		ImageIO.write(set, "png", outFile);
	}
}
