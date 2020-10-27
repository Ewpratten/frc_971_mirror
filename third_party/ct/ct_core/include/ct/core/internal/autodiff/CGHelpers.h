/**********************************************************************************************************************
This file is part of the Control Toolbox (https://adrlab.bitbucket.io/ct), copyright by ETH Zurich, Google Inc.
Authors:  Michael Neunert, Markus Giftthaler, Markus Stäuble, Diego Pardo, Farbod Farshidian
Licensed under Apache2 license (see LICENSE file in main directory)
**********************************************************************************************************************/

#pragma once

#include "SparsityPattern.h"
#include <cppad/local/jacobian.hpp>

namespace ct {
namespace core {
namespace internal {

//! Utility class for Auto-Diff code generation
class CGHelpers
{
public:
    //! default constructor
    CGHelpers(){};

    //! destructor
    virtual ~CGHelpers(){};

    //! generate source code for Jacobian
    /*!
	 * This method generates C source code for a Jacobian generated by Auto Differentiation.
	 *
	 * It generates C source code but does not write it to file. A sparsity pattern can be provided
	 * to only get certain elements of the Jacobian. Zero entries in the Jacobian are automatically
	 * detected and do not need to be defined sparse. Optionally, a flag can be set to explicitely
	 * ignore the zero entries of the Jacobian. If so, it is assumed that all entries of the Jacobian
	 * are set to zero outside of the generated code.
	 *
	 * @param f Auto-Diff function
	 * @param x_dim input dimension of independent (input) variable
	 * @param jac returns the resulting Jacobian
	 * @param pattern sparsity pattern defining which entries of the Jacobian to generate
	 * @param maxTempVarCount number of temporary variables in the resulting source code
	 * @param useReverse if true, Auto-Diff reverse mode will be used
	 * @param ignoreZero if true, the source code will not set zero entries in the Jacobian
	 * @param jacName name of the Jacobian variable in the source code
	 * @param inputName name of the independent (input) variable of the Jacobian
	 * @param tempName name of temporary variables (i.e. an array / vector)
	 * @return generated C source code
	 * @tparam AD_SCALAR Auto-Diff scalar type which is either a normal AD type or a codegen type
   * @tparam SCALAR underlying primitive type
	 */
    template <typename AD_SCALAR, typename SCALAR = double>
    static std::string generateJacobianSource(CppAD::ADFun<AD_SCALAR>& f,
        SparsityPattern& pattern,
        const size_t jacDim,
        size_t& maxTempVarCount,
        bool useReverse = false,
        bool ignoreZero = true,
        std::string jacName = "jac",
        std::string inputName = "x_in",
        std::string tempName = "v_",
        std::string scalarName = "double")
    {
        CppAD::cg::CodeHandler<SCALAR> codeHandler;

        size_t n = f.Domain();

        CppAD::vector<AD_SCALAR> input(n);
        codeHandler.makeVariables(input);
        // Initializing to some typical values
        for (size_t i = 0; i < n; i++)
            input[i].setValue(0.0);

        CppAD::vector<AD_SCALAR> jac(jacDim);

        if (useReverse)
            f.SparseJacobianReverse(
                input, pattern.sparsity(), pattern.row(), pattern.col(), jac, pattern.workJacobian());
        else
            f.SparseJacobianForward(
                input, pattern.sparsity(), pattern.row(), pattern.col(), jac, pattern.workJacobian());

        CppAD::cg::LanguageC<SCALAR> langC(scalarName, 4);
        langC.setIgnoreZeroDepAssign(ignoreZero);
        CppAD::cg::LangCDefaultVariableNameGenerator<SCALAR> nameGen(jacName, inputName, tempName);

        std::ostringstream code;
        codeHandler.generateCode(code, langC, jac, nameGen);

        std::cout << "temporary variables: " << codeHandler.getTemporaryVariableCount() << std::endl;
        maxTempVarCount = codeHandler.getTemporaryVariableCount();

        return code.str();
    }

    //! Generates code for the "zero order" derivative
    /*!
	 * This method generates C code for the "zero order" derivative, i.e. the original function/model
	 * itself. While this seems unusual at first, Auto-Diff can optimize regular function calls and
	 * generate more efficient code. The resulting code should have comparable numerical accuracy as
	 * the original model.
	 *
	 * @param f The function to generate source code for
	 * @param x_dim input dimension of independent (input) variable
	 * @param jac zero-order Jacobian
	 * @param maxTempVarCount number of temporary variables in the resulting source code
	 * @param ignoreZero if true, the source code will not set zero entries in the Jacobian
	 * @param jacName name of the Jacobian variable in the source code
	 * @param inputName name of the independent (input) variable of the Jacobian
	 * @param tempName name of temporary variables (i.e. an array / vector)
	 * @return
	 * @tparam AD_SCALAR Auto-Diff scalar type which is either a normal AD type or a codegen type
	 */
    template <typename AD_SCALAR>
    static std::string generateForwardZeroSource(CppAD::ADFun<AD_SCALAR>& f,
        size_t& maxTempVarCount,
        bool ignoreZero = true,
        std::string jacName = "forwardZero",
        std::string inputName = "x_in",
        std::string tempName = "v_")
    {
        CppAD::cg::CodeHandler<double> codeHandler;

        // input vector, needs to be dynamic size
        size_t n = f.Domain();

        CppAD::vector<AD_SCALAR> input(n);

        for (size_t i = 0; i < input.size(); i++)
            input[i] = AD_SCALAR(0.0);

        // mark independent as variables
        codeHandler.makeVariables(input);

        CppAD::vector<AD_SCALAR> forwardZero = f.Forward(0, input);

        CppAD::cg::LanguageC<double> langC("double", 4);
        langC.setIgnoreZeroDepAssign(ignoreZero);
        CppAD::cg::LangCDefaultVariableNameGenerator<double> nameGen(jacName, inputName, tempName);

        std::ostringstream code;
        codeHandler.generateCode(code, langC, forwardZero, nameGen);

        std::cout << "temporary variables: " << codeHandler.getTemporaryVariableCount() << std::endl;
        maxTempVarCount = codeHandler.getTemporaryVariableCount();

        return code.str();
    }

    //! generate source code for Hessian
    /*!
	 * This method generates C source code for a Hessian generated by Auto Differentiation.
	 *
	 * It generates C source code but does not write it to file. A sparsity pattern can be provided
	 * to only get certain elements of the Hessian. Zero entries in the Hessian are automatically
	 * detected and do not need to be defined sparse. Optionally, a flag can be set to explicitely
	 * ignore the zero entries of the Hessian. If so, it is assumed that all entries of the Hessian
	 * are set to zero outside of the generated code.
	 *
	 * @param f Auto-Diff function
	 * @param pattern sparsity pattern defining which entries of the Hessian to generate
	 * @param hesDim the dimension of the Hessian to generate
	 * @param maxTempVarCount number of temporary variables in the resulting source code
	 * @param useReverse if true, Auto-Diff reverse mode will be used
	 * @param ignoreZero if true, the source code will not set zero entries in the Hessian
	 * @param jacName name of the Hessian variable in the source code
	 * @param inputName name of the independent (input) variable of the Hessian
	 * @param tempName name of temporary variables (i.e. an array / vector)
	 * @return generated C source code
	 * @tparam AD_SCALAR Auto-Diff scalar type which is either a normal AD type or a codegen type
	 */
    template <typename AD_SCALAR>
    static std::string generateHessianSource(CppAD::ADFun<AD_SCALAR>& f,
        SparsityPattern& pattern,
        const size_t hesDim,
        size_t& maxTempVarCount,
        bool ignoreZero = true,
        std::string jacName = "hes",
        std::string inputName = "x_in",
        std::string tempName = "v_")
    {
        CppAD::cg::CodeHandler<double> codeHandler;

        size_t m = f.Range();
        size_t n = f.Domain();

        CppAD::vector<AD_SCALAR> input(n);
        codeHandler.makeVariables(input);
        // setting some typical values here.
        for (size_t i = 0; i < input.size(); i++)
            input[i].setValue(0.0);

        CppAD::vector<AD_SCALAR> weights(m);
        codeHandler.makeVariables(weights);
        // settings some typical values for the weights
        for (size_t i = 0; i < m; ++i)
            weights[i].setValue(0.0);

        CppAD::vector<AD_SCALAR> hes(hesDim);
        f.SparseHessian(input, weights, pattern.sparsity(), pattern.row(), pattern.col(), hes, pattern.workHessian());

        // make use of the symmetry of the hessian
        for (size_t i = 0; i < n; i++)
            for (size_t j = 0; j < i; j++)
                hes[i * n + j] = hes[j * n + i];

        CppAD::cg::LanguageC<double> langC("double", 4);
        langC.setIgnoreZeroDepAssign(ignoreZero);
        CppAD::cg::LangCDefaultVariableNameGenerator<double> nameGenTmp(jacName, inputName, tempName);
        CppAD::cg::LangCDefaultHessianVarNameGenerator<double> nameGen(&nameGenTmp, "w_in", m);

        std::ostringstream code;
        codeHandler.generateCode(code, langC, hes, nameGen);

        std::cout << "temporary variables: " << codeHandler.getTemporaryVariableCount() << std::endl;
        maxTempVarCount = codeHandler.getTemporaryVariableCount();

        return code.str();
    }


    //! replaces all occurrences of a (sub-)string in a string with a replacement string
    /*!
	 *
	 * @param text the string to modify
	 * @param placeholder the substring to search for and replace
	 * @param replaceWith the string replacing the found pattern with
	 */
    static void replaceAll(std::string& text, const std::string& placeholder, const std::string replaceWith)
    {
        size_t pos = text.find(placeholder);
        while (pos != std::string::npos)
        {
            text.replace(pos, placeholder.length(), replaceWith);
            pos = text.find(placeholder);
        }
    }

    //! replaces the first occurrence of a (sub-)string in a string with a replacement string
    /*!
	 *
	 * @param text the string to modify
	 * @param placeholder the substring to search for and replace
	 * @param replaceWith the string replacing the found pattern with
	 */
    static void replaceOnce(std::string& text, const std::string& placeholder, const std::string replaceWith)
    {
        text.replace(text.find(placeholder), placeholder.length(), replaceWith);
    }

    //! write a string to file
    /*!
	 * writes a text to a new file
	 * @param outputFile path of the file to write
	 * @param content content to write to the file
	 */
    static void writeFile(const std::string& outputFile, const std::string& content)
    {
        std::ofstream out(outputFile);

        if (!out.good())
        {
            std::cout << "Could not open output file for writing " << outputFile << std::endl;
            out.close();
            throw std::runtime_error("Code generation failed. Exiting.");
        }

        std::cout << "Writing generated code to file... " << std::endl;

        out << content;
        out.close();
    }

    //! read the contents of a file to string
    /*!
	 * Opens a file and reads all its content to a string
	 * @param filename path of the file to read
	 * @return content of the file
	 */
    static std::string parseFile(const std::string& filename)
    {
        std::ifstream t(filename);

        if (!t.good())
        {
            std::cout << "Could not open template file " << filename << std::endl;
            std::cout << "Code generation failed. Exiting." << std::endl;
            t.close();
            throw std::runtime_error("Code generation failed. Exiting.");
        }

        std::stringstream stream;
        stream << t.rdbuf();

        std::string source(stream.str());

        t.close();

        return source;
    }
};

} /* namespace internal */
} /* namespace core */
} /* namespace ct */