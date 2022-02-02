import ij.*;
import ij.gui.*;
import ij.plugin.filter.*;
import ij.process.*;
import java.awt.*;

public class Histogramme_ implements PlugInFilter {
    public void run(ImageProcessor ip) {
        ImagePlus impHisto = NewImage.createByteImage(
                "Histogramme", 256, 256, 1, NewImage.FILL_WHITE);
        ImageProcessor ipHisto = impHisto.getProcessor();
        ipHisto.setColor(Color.black);

        /**
         *
         * Contraintes:
         * - largeur d'une barre de l'histogramme: 1 pixel
         * - taille de l'histogramme: 256x256 pixels
         *
         * Pour lire le niveau de gris d'un pixel, utiliser la méthode
         * int ImageProcessor.getPixel(int x, int y)
         *
         * Pour tracer une ligne sure image, utiliser la méthode
         * void ImageProcessor.drawLine(int x1, int y1, int x2, int y2)
         */

        // On va stocker l'histogramme dans un tableau d'entiers.
        // Chaque case i de ce tableau contiendra le nombre d'occurrences
        // du niveau de gris i dans l'image.
        int[] histo = new int[256];
        for (int i = 0; i < 256; i++) {
            histo[i] = 0;
        }

        // On compte...
        for (int y = 0; y < ip.getHeight(); y++) {
            for (int x = 0; x < ip.getWidth(); x++) {
                histo[ip.getPixel(x, y)]++;
            }
        }

        // On veut dessiner l'histogramme dans une fenêtre de hauteur 256.
        // Autrement dit, on veut que la hauteur de la plus grande barre de
        // l'histogramme soit 256.
        // Il va donc falloir faire une mise à l'échelle (règle de 3).
        int max = 0;
        for (int i = 0; i < 256; i++) {
            if (histo[i] > max) max = histo[i];
        }

        for (int i = 0; i < 256; i++) {
            int hauteur = histo[i] * 256 / max;

            if (hauteur > 0) {
                ipHisto.drawLine(i, 255, i, 256 - hauteur);
            }
        }

        /**
         * Fin de la partie à compléter.
         */
        new ImageWindow(impHisto);
    }

    public int setup(String arg, ImagePlus imp) {
        return NO_CHANGES + DOES_8G;
    }
}
