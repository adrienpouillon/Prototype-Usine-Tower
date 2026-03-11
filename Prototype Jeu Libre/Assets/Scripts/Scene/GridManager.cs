using NUnit.Framework;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class GridManager : MonoBehaviour
{
    // SINGLETON
    public static GridManager Instance { get; private set; }

    private void Awake()
    {
        if (Instance != null && Instance != this)
        {
            Destroy(this.gameObject);
            return;
        }
        Instance = this;
    }

    // MEMBERS
    private Dictionary<UnityEngine.Vector2, (GameObject occupant, GameObject orderer)> m_occupiedCoordinates = new Dictionary<UnityEngine.Vector2, (GameObject, GameObject)>();


    /// TOOLS
    public bool IsFree(UnityEngine.Vector2 coordinate)
    {
        return !m_occupiedCoordinates.ContainsKey(coordinate);
    }

    /// METHODS
    private void Start()
    {
        // PRE BOOK
    }

    public GameObject GetOrderer(UnityEngine.Vector2 coordinate)
    {
        if (IsFree(coordinate))
            return null;
        return m_occupiedCoordinates[coordinate].orderer;
    }

    public bool HaveOrder(GameObject orderer)
    {
        foreach(var entry in m_occupiedCoordinates)
        {
            if(entry.Value.orderer == orderer)
                return true;
        }
        return false;
    }

    public GameObject GetOccupant(UnityEngine.Vector2 coordinate)
    {
        if (IsFree(coordinate))
            return null;
        return m_occupiedCoordinates[coordinate].occupant;
    }

    public bool BookCoordinate(UnityEngine.Vector2 coordinate, GameObject orderer, GameObject occupant)
    {
        if (IsFree(coordinate))
        {
            m_occupiedCoordinates.Add(coordinate, (occupant, orderer));
            return true;
        }
        return false;
    }

    public bool ReleaseCoordinate(UnityEngine.Vector2 coordinate)
    {
        if(IsFree(coordinate))
            return false;

        m_occupiedCoordinates.Remove(coordinate);
        return true;
    }
}
