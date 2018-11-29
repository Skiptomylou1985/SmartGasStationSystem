//////////////////////////////////////////////////////////////////////////
//Commit:   XML配置文件操作类，包含获取指定键值、设定指定键值(最多支持3层)
//Author:   DQS
//Date：    2012-08-24
//Version:  1.0
//////////////////////////////////////////////////////////////////////////
using System;
using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Xml;
using System.IO;

namespace SPManager
{
    
        static class XMLUnit
        {
            static XmlDocument xDoc = new XmlDocument();

            /*
            XMLUnit(string XMLFilePath)
            {
                this.XMLFilePath = XMLFilePath;
                try
                {
                    xDoc = new XmlDocument();
                    xDoc.Load(XMLFilePath);
                
                }
                catch (Exception ex)
                {
                    Log.WriteLog("XMLUnit", "Error", "创建XmlDocument失败:" + ex.Message);
                }            
            }
             * */
            /************************************************************************
             * Function: Get Value of The Key
             * IN:  string XMLFilePath, XML File Path
             *      string RootNode, Root Node
             *      string Section, Section of key
             *      string Key, Key to Get Value
             * OUT: string
             * Author: DQS
             * Date: 2012-08-23
            ************************************************************************/
            public static string XmlGetValue(string XMLFilePath, string RootNode, string Section, string Key)
            {
                string Value = "";
                try
                {
                    if (File.Exists(XMLFilePath))
                    {
                        xDoc.Load(XMLFilePath);
                        XmlNodeList nodeList;
                        XmlNode root = xDoc.SelectSingleNode(RootNode);
                        nodeList = root.SelectNodes(Section + "/" + Key);
                        foreach (XmlNode node in nodeList)
                        {
                            //  if (Key == node.Name)
                            Value = node.InnerText.ToString();
                            break;
                        }
                    }
                    else
                    {
                        
                        return Value;
                    }
                }
                catch (Exception ex)
                {
                    //Log.WriteLog("XMLUnit", "Error", "读取参数" + Key + "失败:" + ex.Message);
                }
                finally
                {
                    xDoc.RemoveAll();
                    // xDoc = null;
                }
                return Value;
            }

            /************************************************************************
             * Function: Set Value of The Key
             * IN:  string XMLFilePath, XML File Path
             *      string RootNode, Root Node
             *      string Section, Section of key
             *      string Key, Key to Set Value
             * OUT: void
             * Author: DQS
             * Date: 2012-08-23
             * Commit: Support at most 3 level node, more not effective
            ************************************************************************/
            public static void XMLSetValue(string XMLFilePath, string RootNode, string Section, string Key, string Value)
            {
                try
                {
                    if (File.Exists(XMLFilePath))
                        xDoc.Load(XMLFilePath);
                    else
                    {
                        if (CreateXMLFile(XMLFilePath, RootNode))
                            xDoc.Load(XMLFilePath);
                        else
                            return;
                    }
                    XmlNodeList nodeList;
                    XmlNode root = xDoc.SelectSingleNode(RootNode);

                    nodeList = root.SelectNodes(Section + "/" + Key);
                    if (0 == nodeList.Count)
                    {
                        nodeList = root.SelectNodes(Section);
                        if (0 == nodeList.Count)
                        {
                            XmlElement newElement = xDoc.CreateElement(Section);
                            XmlElement newSubElement = xDoc.CreateElement(Key);
                            newSubElement.InnerText = Value;
                            newElement.AppendChild(newSubElement);
                            root.AppendChild(newElement);
                            xDoc.Save(XMLFilePath);
                        }
                        else
                        {
                            foreach (XmlNode xmlnode in nodeList)
                            {
                                XmlElement newElement = xDoc.CreateElement(Key);
                                newElement.InnerText = Value;
                                xmlnode.AppendChild(newElement);
                                xDoc.Save(XMLFilePath);
                                break;
                            }
                        }
                    }
                    else
                    {
                        foreach (XmlNode node in nodeList)
                        {
                            //if (Key == node.Name)
                            node.InnerText = Value;
                            xDoc.Save(XMLFilePath);
                            //XmlTextWriter writer = new XmlTextWriter(XMLFilePath, Encoding.UTF8);
                            //writer.Formatting = Formatting.Indented;
                            //xDoc.Save(writer);
                            //writer.Close();
                            break;
                        }
                    }
                }
                catch (Exception ex)
                {
                    //Log.WriteLog("XMLUnit", "Error", "设置参数" + Key + "失败:" + ex.Message);
                }
                finally
                {
                    xDoc.RemoveAll();
                }
            }

            /************************************************************************
             * Function: Delete the Section Node in XML file
             * IN:  string XMLFilePath, XML File Path
             *      string RootNode, Root Node
             *      string Section, Section of key
             * OUT: void
             * Author: DQS
             * Date: 2012-08-24
             * Commit: 
            ************************************************************************/
            public static void XMLDelSection(string XMLFilePath, string RootNode, string Section)
            {
                try
                {
                    if (File.Exists(XMLFilePath))
                    {
                        xDoc.Load(XMLFilePath);
                        XmlNode root = xDoc.SelectSingleNode(RootNode);

                        XmlNode section = root.SelectSingleNode(Section);
                        if (null != section)
                        {
                            root.RemoveChild(section);
                            xDoc.Save(XMLFilePath);
                        }
                    }
                    else
                    {
                        //Log.WriteLog("XMLUnit", "Error", "删除节点" + Section + "失败: 文件不存在");
                        return;
                    }
                }
                catch (Exception ex)
                {
                    //Log.WriteLog("XMLUnit", "Error", "删除区段" + Section + "失败:" + ex.Message);
                }
                finally
                {
                    xDoc.RemoveAll();
                }
            }

            /************************************************************************
             * Function: Delete the Key node in XML File
             * IN:  string XMLFilePath, XML File Path
             *      string RootNode, Root Node
             *      string Section, Section of key
             *      string Key, Key to Set Value
             * OUT: void
             * Author: DQS
             * Date: 2012-08-24
             * Commit:
            ************************************************************************/
            public static void XMLDelKey(string XMLFilePath, string RootNode, string Section, string Key)
            {
                try
                {
                    if (File.Exists(XMLFilePath))
                    {
                        xDoc.Load(XMLFilePath);
                        XmlNode root = xDoc.SelectSingleNode(RootNode);

                        XmlNode section = root.SelectSingleNode(Section);
                        if (null != section)
                        {
                            XmlNode key = section.SelectSingleNode(Key);
                            if (null != key)
                            {
                                section.RemoveChild(key);
                                xDoc.Save(XMLFilePath);
                            }
                        }
                    }
                    else
                    {
                        //Log.WriteLog("XMLUnit", "Error", "删除节点" + Key + "失败: 文件不存在");
                        return;
                    }
                }
                catch (Exception ex)
                {
                    //Log.WriteLog("XMLUnit", "Error", "删除区段" + Section + "失败:" + ex.Message);
                }
                finally
                {
                    xDoc.RemoveAll();
                }
            }

            /************************************************************************
             * Function: Create XML File
             * IN:  string XMLFilePath, XML File Path
             *      string RootNode, Root Node to be Create
             * OUT: bool, true for success, false for failed
             * Author: DQS
             * Date: 2012-08-24
             * Commit:
            ************************************************************************/
            private static bool CreateXMLFile(string XMLFilePath, string RootNode)
            {
                try
                {
                    XmlNode xmlnode = xDoc.CreateNode(XmlNodeType.XmlDeclaration, "", "");
                    xDoc.AppendChild(xmlnode);
                    XmlElement xmlelem = xDoc.CreateElement("", RootNode, "");
                    xDoc.AppendChild(xmlelem);
                    xDoc.Save(XMLFilePath);
                }
                catch (Exception ex)
                {
                    //Log.WriteLog("XMLUnit", "Error", "创建XML文件失败：" + ex.Message);
                    return false;
                }
                finally
                {
                    xDoc.RemoveAll();
                }

                return true;
            }
        }
    
    
}
