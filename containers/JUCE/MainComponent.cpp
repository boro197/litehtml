/*
  ==============================================================================

This file was auto-generated!

    ==============================================================================
    */

#include "MainComponent.h"

        //==============================================================================
        MainComponent::MainComponent()
{
    setSize (1000, 800);

    m_HtmlContainer = std::shared_ptr<container_juce>(new container_juce(32));
    std::string htmlStr = u8"";

    htmlStr += R"raw(
               <html>
               <head>
               <link rel="stylesheet" href="../../include/master.css">
               </head>
               <body>
               <iframe width="560" height="315" src="https://www.youtube.com/embed/Dcb-nLZozos" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
               <a href="http://google.pl/">This is link to google page</a></br>

               bcabcab</br>\ncabcabcabc
               <ul style="list-style-type:decimal;">
               <li>Coffee</li>
               <li>Tea</li>
               <li>Milk</li>
               </ul>

               <a href="https://zylia.co/">This is link to ZYLIA page</a></br></br></br></br>

                <table style="width:100%">
                  <tr>
                    <th>Firstname</th>
                    <th>Lastname</th>
                    <th>Age</th>
                  </tr>
                  <tr>
                    <td>Jill</td>
                    <td>Smith</td>
                    <td>50</td>
                  </tr>
                  <tr>
                    <td>Eve</td>
                    <td>Jackson</td>
                    <td>94</td>
                  </tr>
                </table>


               <b><font color="red">URLS</font></b>
               <ul style="list-style-type:decimal-leading-zero;">
               <li><a href="https://google.pl/">Google</a></li>
               <li><a href="https://github.com/">Github</a></li>
               <li><a href="https://juce.com/">JUCE</a></li>
               </ul>

               <ul style="list-style-type:circle;">
               <li>Coffee</li>
               <li>Tea</li>
               <li>Milk</li>
               </ul>

               <ul style="list-style-type:lower-greek;">
               <li>Coffee</li>
               <li>Tea</li>
               <li>Milk</li>
               </ul>

               <ul style="list-style-type:square;">
               <li>Coffee</li>
               <li>Tea</li>
               <li>Milk</li>
               </ul>
               </body>
               </html>
               )raw";

    m_Document = litehtml::document::createFromUTF8(htmlStr.c_str(), m_HtmlContainer.get(), &ctxt);
    m_HtmlContainer->setDocument(m_Document);
    addAndMakeVisible(m_HtmlContainer.get());
    addChildComponent(m_HtmlContainer.get());
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
    m_HtmlContainer->setBounds(getLocalBounds());
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
