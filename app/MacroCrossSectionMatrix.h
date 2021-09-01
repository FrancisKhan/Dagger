#ifndef MACROCROSSSECTIONMATRIX_H
#define MACROCROSSSECTIONMATRIX_H

#include <vector>
#include <string>

class MacroCrossSectionMatrix
{
public:
    MacroCrossSectionMatrix(double t, const std::vector<std::string> &n, const std::vector<double> &d) : 
                      temperature_(t), nuclides_(n), densities_(d) {}

    MacroCrossSectionMatrix() : temperature_(0.0), nuclides_(std::vector<std::string> {}),
                                densities_(std::vector<double> {}) {}
    void setTemperature(double t) {temperature_ = t;}
    double getTemperature() const {return temperature_;} 
    void setNuclides(const std::vector<std::string>& nuclides) {nuclides_ = nuclides;}
    std::vector<std::string> getNuclides() const {return nuclides_;}
    void setDensities(const std::vector<double>& densities) {densities_ = densities;}
    std::vector<double> getDensities() const {return densities_;}

private:
    double temperature_;
    std::vector<std::string> nuclides_;
    std::vector<double> densities_;
};

#endif