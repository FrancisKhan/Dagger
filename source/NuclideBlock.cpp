#include "NuclideBlock.h"
#include "inputParser.h"
#include "Output.h"
#include "additionalPrintFuncs.h"
#include "numeric_tools.h"

#include <cstdint>
#include <iostream>

using namespace Eigen;

std::pair<unsigned, unsigned> NuclideBlock::getNumberOfValuesToRead(unsigned lineNumber)
{
    std::string line = InputParser::getLine(xsDataLines_, lineNumber);   
    std::vector<std::string> lineVec = InputParser::splitLine(line);

    unsigned kind    = std::stoi(lineVec.end()[-2]); // int or float
    unsigned numbers = std::stoi(lineVec.end()[-1]); // number of values

    return std::make_pair(kind, numbers);
}

unsigned NuclideBlock::getNumberOfLinesToRead(unsigned lineNumber)
{
    unsigned numberOfLines = 0;
    std::pair<unsigned, unsigned> valuePair = getNumberOfValuesToRead(lineNumber);

    double numberOfValues = static_cast<double>(valuePair.second); // to avoid an integer division

    if(valuePair.first == 1) // it is a vector of integers in 8-column rows
    {
        numberOfLines = ceil(numberOfValues / 8);
    }
    else if(valuePair.first == 2) // it is a vector of doubles in 5-column rows
    {
        numberOfLines = ceil(numberOfValues / 5);
    }
    else
    {
        out.print(TraceLevel::CRITICAL, "ERROR: NuclideBlock::getNumberOfLinesToRead, {} value kind not recognized!", 
                  int(valuePair.first));
        throw std::runtime_error("ERROR: NuclideBlock::getNumberOfLinesToRead, {} value kind not recognized!");
    }

    return numberOfLines;
}

std::vector<double> NuclideBlock::readParameters(const std::string &key, unsigned lowerBound, unsigned upperBound)
{
    std::vector<double> result;

    std::vector<unsigned> lines = InputParser::findLine(xsDataLines_, key, lowerBound, upperBound);

    if (lines.size() > 0)
    {
        unsigned linesToRead = getNumberOfLinesToRead(lines.front() - 1);

        std::vector<std::string> resultStringsFinal;
        std::vector<std::string> resultStrings;

        for(unsigned i = lines.front() + 1; i <= lines.front() + linesToRead; i++)
        {
            resultStrings = InputParser::splitLine(InputParser::getLine(xsDataLines_, i));
            resultStringsFinal.insert(resultStringsFinal.end(), resultStrings.begin(), resultStrings.end());     
        } 

        result = InputParser::fromStringVecToDoubleVec(resultStringsFinal);
    }

    return result;
}

void NuclideBlock::setNumberOfEnergyGroups()
{
    nuclide_->setEnergyGroupsNumber(numberOfEnergyGroups_);   
}

void NuclideBlock::readName()
{
    nuclide_->setName(InputParser::getLine(xsDataLines_, 1));   
}

void NuclideBlock::readAWR()
{
    const std::string key = "AWR"; 
    std::vector<double> results = readParameters(key);
    nuclide_->setAWR(results.front());   
}

std::vector<double> NuclideBlock::readTemperatures()
{
    const std::string key = "TEMPERATURE"; 
    std::vector<double> v = readParameters(key);
    nuclide_->setTemperatures(v);
    return v;
}

std::vector< std::pair<unsigned, unsigned> > NuclideBlock::readTemperatureBlocks()
{
    const std::string key = "SUBTMP"; 
    std::vector<unsigned> tempBlocklines;

    for(unsigned i = 0; i < readTemperatures().size(); i++)
    {
        std::string compositeKey = key + PrintFuncs::stringFormat(i + 1, "%04d"); 
        std::vector<unsigned> lines = InputParser::findLine(xsDataLines_, compositeKey);

        if(lines.size() == 1)
        {
            tempBlocklines.push_back(lines.front());
        }
        else
        {
            out.print(TraceLevel::CRITICAL, "ERROR: {} seems to repeat in the XS library!", key);
            throw std::runtime_error("ERROR: key seems to repeat in the XS library!");
        }
    }

    std::vector< std::pair<unsigned, unsigned> > blockLinesVec;

    for(size_t i = 0; i < tempBlocklines.size() - 1; i++)
        blockLinesVec.push_back(std::make_pair(tempBlocklines[i], tempBlocklines[i + 1]));

    blockLinesVec.push_back(std::make_pair(tempBlocklines[tempBlocklines.size() - 1], xsDataLines_.size()));

    return blockLinesVec;
}

std::vector<double> NuclideBlock::readDilutions(unsigned firstLine, unsigned lastLine)
{
    const std::string key = "DILUTION"; 
    std::vector<double> v = readParameters(key, firstLine, lastLine);
    v.push_back(Numerics::DINF); // the infinite dilution value does not explicitly appears on the DILUTION list
    
    std::vector<double> dilutions = nuclide_->getDilutions();
    if((dilutions.size() != 0) && (v != dilutions))
    {
        out.print(TraceLevel::CRITICAL, "ERROR: {} seems to have temperature-dependent dilution values!", 
        nuclide_->getName());
        throw std::runtime_error("ERROR: nuclide seems to have temperature-dependent dilution values!");
    }

    nuclide_->setDilutions(v);
    return v;
}

std::vector< std::pair<unsigned, unsigned> > 
NuclideBlock::readDilutionBlocks(std::pair<unsigned, unsigned> &block)
{
    const std::string key = "SUBMAT"; 
    std::vector<unsigned> dilBlocklines;

    // don't look for infinite dilution
    for(unsigned i = 0; i < readDilutions(block.first, block.second).size() - 1; i++)
    {
        std::string compositeKey = key + PrintFuncs::stringFormat(i + 1, "%04d"); 
        std::vector<unsigned> lines = InputParser::findLine(xsDataLines_, compositeKey, block.first, block.second);

        if(lines.size() == 1)
        {
            dilBlocklines.push_back(lines.front());
        }
        else
        {
            out.print(TraceLevel::CRITICAL, "ERROR: {} seems to repeat in the XS library!", key);
            throw std::runtime_error("ERROR: key seems to repeat in the XS library!");
        }
    }

    std::vector< std::pair<unsigned, unsigned> > blockLinesVec;

    for(size_t i = 0; i < dilBlocklines.size() - 1; i++)
        blockLinesVec.push_back(std::make_pair(dilBlocklines[i], dilBlocklines[i + 1]));

    blockLinesVec.push_back(std::make_pair(dilBlocklines[dilBlocklines.size() - 1], xsDataLines_.size()));
    
    return blockLinesVec;
}

std::pair<unsigned, unsigned> NuclideBlock::readInfDilutionBlock(std::pair<unsigned, unsigned> &block)
{
    const std::string key1 = "->      -4       0       0       0";
    const std::string key2 = "->       3      12       2     172"; 

    std::vector<unsigned> key1Lines = InputParser::findLine(xsDataLines_, key1, block.first, block.second);

    std::vector<unsigned> key2Lines;
    for(auto i : key1Lines)
    {
        key2Lines = InputParser::findLine(xsDataLines_, key2, i, i + 2);
        if (key2Lines.size() > 0) break;
    }

    return std::make_pair(key2Lines.front(), block.second);
}

std::vector<double> NuclideBlock::populateXS(std::vector<double> &xsVec) 
{
    std::vector<double> result;
    size_t inputSize = xsVec.size(); 

        if (inputSize < getNumberOfEnergyGroups())
        {
            std::vector<double> temp(getNumberOfEnergyGroups() - inputSize, 0.0);
            xsVec.insert(xsVec.end(), temp.begin(), temp.end()); 
            result = xsVec;
        }
        else if(inputSize == getNumberOfEnergyGroups())
        {
            result = xsVec;
        }
        else
        {
            out.print(TraceLevel::CRITICAL, "ERROR: {} read in the XS library!", int(inputSize));
            throw std::runtime_error("ERROR: wrong number of values read in the XS library!");
        }

    return result;
}

std::vector<Nuclide::XSSetType> NuclideBlock::readXSs()
{
    std::vector< std::pair<unsigned, unsigned> > tempBlocks = readTemperatureBlocks();
    std::vector<double> temperatures = nuclide_->getTemperatures();

    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();

    for (const auto& xsKind : XSKind())
    {
        CrossSectionSet& crossSectionSet = Nuclide::getXSSet(xsKind, crossSectionSets);

        for(size_t i = 0; i < temperatures.size(); i++)
        {
            if(nuclide_->isResonant())
            {
                // Infinite dilution XSs

                if(xsKind == XSKind::NTOT0)
                {
                    std::vector<double> xsVecPartial = readParameters(get_name(xsKind), tempBlocks[i].first, tempBlocks[i].second);
                    std::vector<double> xsVec = populateXS(xsVecPartial);
                    CrossSection crossSection(temperatures[i], Numerics::DINF, xsVec);
                    crossSectionSet.addXS(crossSection);
                }

                // The following line is needed because the fine-structure function (NWT0) infinite
                // dilution values are ones and they are not stored in the library
                else if(xsKind == XSKind::NWT0)
                {
                    std::vector<double> xsVec(getNumberOfEnergyGroups(), 1.0);
                    CrossSection crossSection(temperatures[i], Numerics::DINF, xsVec);
                    crossSectionSet.addXS(crossSection);
                }
                else
                {
                    std::pair<unsigned, unsigned> infDilutionBlock = readInfDilutionBlock(tempBlocks[i]);
                    std::vector<double> xsVecPartial = readParameters(get_name(xsKind), infDilutionBlock.first, infDilutionBlock.second);
                    std::vector<double> xsVec = populateXS(xsVecPartial);
                    CrossSection crossSection(temperatures[i], Numerics::DINF, xsVec);
                    crossSectionSet.addXS(crossSection);
                }

                // other dilution XSs

                std::vector< std::pair<unsigned, unsigned> > dilutionBlocks = readDilutionBlocks(tempBlocks[i]);
                std::vector<double> dilutions = readDilutions(tempBlocks[i].first, tempBlocks[i].second);

                for(size_t j = 0; j < dilutions.size() - 1; j++) // don't look for infinite dilution
                {
                    std::vector<double> xsVecPartial = readParameters(get_name(xsKind), dilutionBlocks[j].first, dilutionBlocks[j].second);
                    std::vector<double> xsVec = populateXS(xsVecPartial);
                    CrossSection crossSection(temperatures[i], dilutions[j], xsVec);
                    crossSectionSet.addXS(crossSection);
                }
            }
            else // non-resonant isotope
            {
                // The following line is needed because the fine-structure function (NWT0) infinite
                // dilution values are ones and they are not stored in the library
                if(xsKind != XSKind::NWT0)
                {
                    std::vector<double> xsVecPartial = readParameters(get_name(xsKind), tempBlocks[i].first, tempBlocks[i].second);
                    std::vector<double> xsVec = populateXS(xsVecPartial);
                    CrossSection crossSection(temperatures[i], Numerics::DINF, xsVec);
                    crossSectionSet.addXS(crossSection);
                }
                else
                {
                    std::vector<double> xsVec(getNumberOfEnergyGroups(), 1.0);
                    CrossSection crossSection(temperatures[i], Numerics::DINF, xsVec);
                    crossSectionSet.addXS(crossSection);
                }
                
                std::vector<double> dilutions {Numerics::DINF};
                nuclide_->setDilutions(dilutions);
            }
        }
    }

   return crossSectionSets;
}

std::vector<Nuclide::XSMatrixSetType> NuclideBlock::readXSMatrices()
{
    std::vector< std::pair<unsigned, unsigned> > tempBlocks = readTemperatureBlocks();
    std::vector<double> temperatures = nuclide_->getTemperatures();
    
    std::vector<Nuclide::XSMatrixSetType> crossSectionMatrixSets = nuclide_->getCopyOfXSMatrixSets();

    for (const auto& xsKind : XSMatrixKind())
    {
        CrossSectionMatrixSet& crossSectionMatrixSet = Nuclide::getXSMatrixSet(xsKind, crossSectionMatrixSets);

        for(size_t i = 0; i < temperatures.size(); i++)
        {
            if(nuclide_->isResonant())
            {
                // Infinite dilution XSs

                std::pair<unsigned, unsigned> infDilutionBlock = readInfDilutionBlock(tempBlocks[i]);
                MatrixXd matrix = assembleMatrixXS(xsKind, infDilutionBlock.first, infDilutionBlock.second);
                CrossSectionMatrix crossSectionMatrix(temperatures[i], Numerics::DINF, matrix);
                crossSectionMatrixSet.addXS(crossSectionMatrix);

                // other dilution XSs

                std::vector< std::pair<unsigned, unsigned> > dilutionBlocks = readDilutionBlocks(tempBlocks[i]);
                std::vector<double> dilutions = readDilutions(tempBlocks[i].first, tempBlocks[i].second);

                for(size_t j = 0; j < dilutions.size() - 1; j++) // don't look for infinite dilution
                {
                    MatrixXd matrix = assembleMatrixXS(xsKind, dilutionBlocks[j].first, dilutionBlocks[j].second);
                    CrossSectionMatrix crossSectionMatrix(temperatures[i], dilutions[j], matrix);
                    crossSectionMatrixSet.addXS(crossSectionMatrix);
                }
            }
            else // non-resonant isotope
            {
                MatrixXd matrix = assembleMatrixXS(xsKind, tempBlocks[i].first, tempBlocks[i].second);
                CrossSectionMatrix crossSectionMatrix(temperatures[i], Numerics::DINF, matrix);
                crossSectionMatrixSet.addXS(crossSectionMatrix);
            }
        }
    }
    
    return crossSectionMatrixSets;
}

MatrixXd NuclideBlock::assembleMatrixXS(XSMatrixKind xsKind, unsigned lowBound, unsigned upperBound)
{
    if(InputParser::isKeywordPresent(xsDataLines_, get_name(xsKind), lowBound, upperBound))
    {
        MatrixXd M = MatrixXd::Zero(nuclide_->getEnergyGroupsNumber(), nuclide_->getEnergyGroupsNumber());

        std::tuple< std::vector<double>, std::vector<int32_t>, std::vector<int32_t> > vectors = 
        readMatrixComponents(xsKind, lowBound, upperBound);

        std::vector<double> xsVec = std::get<0>(vectors);
        std::vector<int32_t> njj  = std::get<1>(vectors);
        std::vector<int32_t> ijj  = std::get<2>(vectors);

        int32_t energyGroups = nuclide_->getEnergyGroupsNumber();

        for(int32_t h = 0; h < energyGroups; h++)
        {
            for(int32_t g = 0; g < energyGroups; g++)
            {
                int32_t k = 0;

                for(int32_t hh = 0; hh <= g - 1; hh++)
                {
                    k += njj[hh];
                }

                if(!(h > ijj[g] - 1) && !(h < ijj[g] - njj[g]))
                {
                    M(h, g) = xsVec[k + ijj[g] - h - 1];
                }
            }
        }

        return M;
    }
    else
    {
        return MatrixXd::Zero(1, 1);
    } 
}

std::tuple< std::vector<double>, std::vector<int32_t>, std::vector<int32_t> > 
	NuclideBlock::readMatrixComponents(XSMatrixKind xsKind, unsigned lowBound, unsigned upperBound)
{
    std::pair<std::string, std::string> keys = getMatrixKeys(xsKind);

    std::vector<double> xsVec     = readParameters(get_name(xsKind), lowBound, upperBound);
    std::vector<double> njjDouble = readParameters(keys.first, lowBound, upperBound);
    std::vector<double> ijjDouble = readParameters(keys.second, lowBound, upperBound);

    std::vector<int32_t> njj(begin(njjDouble), end(njjDouble));
    std::vector<int32_t> ijj(begin(ijjDouble), end(ijjDouble)); 

    return std::make_tuple(xsVec, njj, ijj);
}

std::pair<std::string, std::string> NuclideBlock::getMatrixKeys(XSMatrixKind xsKind)
{
    std::string key1 = "NJJS0" + std::to_string(static_cast<uint32_t>(xsKind));
    std::string key2 = "IJJS0" + std::to_string(static_cast<uint32_t>(xsKind));
    return std::make_pair(key1, key2);
}

void NuclideBlock::readGroupConstants()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = readXSs();
    nuclide_->setXSSets(crossSectionSets);
    nuclide_->calcXSSets();

    std::vector<Nuclide::XSMatrixSetType> crossSectionMatrixSets = readXSMatrices();
    nuclide_->setXSMatrixSets(crossSectionMatrixSets);
    nuclide_->calcXSMatrixSets();
}

void NuclideBlock::isNuclideResonant()
{
    const std::string key = "DILUTION"; 
    std::vector<double> parVec = readParameters(key);
    bool value = parVec.size() > 0 ? true : false;
    nuclide_->setIsResonant(value);
}

void NuclideBlock::isNuclideFissionable() const
{
    bool isFissionable = nuclide_->getXSSet(XSKind::NFTOT).isEmpty();
    nuclide_->setIsFissionable(!isFissionable);
}

std::vector<double> NuclideBlock::readLambdas()
{
    const std::string key = "LAMBDA-D"; 
    std::vector<double> v = readParameters(key);
    nuclide_->setLambdas(v);
    return v;
}

void NuclideBlock::fromRItoXS()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();
    CrossSectionSet fineStructure = Nuclide::getXSSet(XSKind::NWT0, crossSectionSets);

    for(const auto& xsKind : XSKind())
    {
        if(xsKind > XSKind::NUSIGF) break;

        CrossSectionSet& xs = Nuclide::getXSSet(xsKind, crossSectionSets);
        CrossSectionSet xsOld = xs;

        xs = xsOld / fineStructure;
    }
    
    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::fromRImatrixToXSmatrix()
{
    std::vector<Nuclide::XSMatrixSetType> matrixSets = nuclide_->getCopyOfXSMatrixSets();
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();
    
    CrossSectionSet fineStructure = Nuclide::getXSSet(XSKind::NWT0, crossSectionSets);

    // At the moment, done only for SCATT00
    CrossSectionMatrixSet& mat = Nuclide::getXSMatrixSet(XSMatrixKind::SCAT00, matrixSets);
    CrossSectionMatrixSet matOld = mat;

    mat = matOld / fineStructure;
    
    nuclide_->setXSMatrixSets(matrixSets);
}

void NuclideBlock::addNu()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();
    
    if(nuclide_->isFissionable())
    {
        CrossSectionSet nusigfSet = Nuclide::getXSSet(XSKind::NUSIGF, crossSectionSets);
        CrossSectionSet sigfSet   = Nuclide::getXSSet(XSKind::NFTOT, crossSectionSets);
        CrossSectionSet& nuSet = Nuclide::getXSSet(XSKind::NU, crossSectionSets);
        nuSet.deleteXSs();
        nuSet = nusigfSet / sigfSet;
    }
    
    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::addScatteringL0XS()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();

    CrossSectionSet& xsScatt00Set = Nuclide::getXSSet(XSKind::SCATT00, crossSectionSets);
    xsScatt00Set.deleteXSs();

    CrossSectionMatrixSet matS0 = nuclide_->getXSMatrixSet(XSMatrixKind::SCAT00); 
    xsScatt00Set = matS0.condenseToXSs();

    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::addScatteringL1XS()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();

    CrossSectionSet& xsScatt01Set = Nuclide::getXSSet(XSKind::SCATT01, crossSectionSets);
    xsScatt01Set.deleteXSs();

    CrossSectionMatrixSet matS1 = nuclide_->getXSMatrixSet(XSMatrixKind::SCAT01); 
    
    if(matS1.isEmpty()) // there is no L1 scattering matrix available for this nuclide
    {
        CrossSectionMatrixSet matS0 = nuclide_->getXSMatrixSet(XSMatrixKind::SCAT00); 
        CrossSectionSet xsScatt00Set = matS0.condenseToXSs();
        xsScatt01Set = (2.0 / (3.0 * nuclide_->getAWR())) * xsScatt00Set;
    }
    else
    {
        xsScatt01Set = matS1.condenseToXSs();
    } 

    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::addAbsXS()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();

    CrossSectionSet& absSet = Nuclide::getXSSet(XSKind::ABS, crossSectionSets);
    absSet.deleteXSs();

    CrossSectionSet ngSet   = Nuclide::getXSSet(XSKind::NG, crossSectionSets);
    CrossSectionSet fissSet = Nuclide::getXSSet(XSKind::NFTOT, crossSectionSets);
    CrossSectionSet npSet   = Nuclide::getXSSet(XSKind::NP, crossSectionSets);
    CrossSectionSet ndSet   = Nuclide::getXSSet(XSKind::ND, crossSectionSets);
    CrossSectionSet ntSet   = Nuclide::getXSSet(XSKind::NT, crossSectionSets);
    CrossSectionSet naSet   = Nuclide::getXSSet(XSKind::NA, crossSectionSets);
    CrossSectionSet n2nSet  = Nuclide::getXSSet(XSKind::N2N, crossSectionSets);
    CrossSectionSet n3nSet  = Nuclide::getXSSet(XSKind::N3N, crossSectionSets);

    // opposite to many other formats like MATXS, DRAGON one does a scaling of n2n and n3n XSs
    //absSet = ngSet + fissSet + npSet + ndSet + ntSet + naSet - n2nSet - 2.0 * n3nSet;
    absSet = ngSet + fissSet + npSet + ndSet + ntSet + naSet + n2nSet + n3nSet;

    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::addTranspXS()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();

    CrossSectionSet& transpSet = Nuclide::getXSSet(XSKind::TRANSP, crossSectionSets);
    transpSet.deleteXSs();

    CrossSectionSet totSet = Nuclide::getXSSet(XSKind::NTOT0, crossSectionSets);
    CrossSectionSet scatt01Set = Nuclide::getXSSet(XSKind::SCATT01, crossSectionSets);

    transpSet = totSet - scatt01Set;

    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::modifyChi()
{
    std::vector<Nuclide::XSSetType> crossSectionSets = nuclide_->getCopyOfXSSets();

    CrossSectionSet& chiSet   = Nuclide::getXSSet(XSKind::CHI, crossSectionSets);
    CrossSectionSet chiSetOld = Nuclide::getXSSet(XSKind::CHI, crossSectionSets);
    chiSet.deleteXSs();
    chiSet = 0.5 * chiSetOld;

    nuclide_->setXSSets(crossSectionSets);
}

void NuclideBlock::additionalXSs()
{
    addNu();
    addScatteringL0XS();
    addScatteringL1XS();
    addAbsXS();
    addTranspXS();
    modifyChi();
}

std::shared_ptr<Nuclide> NuclideBlock::getNuclide()
{
    readName();
    readAWR();
    isNuclideResonant();
    setNumberOfEnergyGroups();
	readTemperatureBlocks();
	readGroupConstants();
    isNuclideFissionable();
    readLambdas();
    fromRItoXS();
    fromRImatrixToXSmatrix();
    additionalXSs();
    return nuclide_;
}
