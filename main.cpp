#include "SFML/Graphics.hpp"


const int W = 960;
const int H = 540;


const int max_iter = 120;
double min_re = -2.5;
double max_re = 1;
double min_im = -1;
double max_im = 1;

int main() {

	sf::RenderWindow window(sf::VideoMode(W, H), "Mandelbrot", sf::Style::Close);


    sf::Image image;
    image.create(W, H);
    sf::Texture texture;
    sf::Sprite sprite;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto zoom_x = [&](double z) {
                    double cr = min_re + (max_re - min_re) * event.mouseButton.x / W;
                    double ci = min_im + (max_im - min_im) * event.mouseButton.y / H;

                    double tminr = cr - (max_re - min_re) / 2 / z;
                    max_re = cr + (max_re - min_re) / 2 / z;
                    min_re = tminr;

                    double tmini = ci - (max_im - min_im) / 2 / z;
                    max_im = ci + (max_im - min_im) / 2 / z;
                    min_im = tmini;
                };

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    zoom_x(5);
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    zoom_x(1.0 / 5);
                }
            }
        }



        window.clear();

        for (int y = 0; y < H; y++)
        {
            for (int x = 0; x < W; x++)
            {
                double cr = min_re + (max_re - min_re) * x / W;
                double ci = min_im + (max_im - min_im) * y / H;

                double re = 0;
                double im = 0;

                int iter;
                for (iter = 0; iter < max_iter; iter++)
                {
                    double tr = re * re - im * im + cr;
                    im = 2 * re * im + ci;
                    re = tr;

                    if (re * re + im * im > 2 * 2)
                    {
                        break;
                    }
                }

                int r = 1.0 * (max_iter - iter) / max_iter * 0xff;
                int g = r;
                int b = r;

                image.setPixel(x, y, sf::Color(r, g, b));
            }
        }


        texture.loadFromImage(image);
        sprite.setTexture(texture);

        window.draw(sprite);

        window.display();
    }
	
    return 0;
}